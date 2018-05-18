// Copyright (c) 2018 The DeepOnion Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "rpcconsole.h"
#include "ui_rpcconsole.h"

#include "clientmodel.h"
#include "bitcoinrpc.h"
#include "blockchaindialog.h"
#include "guiutil.h"
#include "bantablemodel.h"
#include "peertablemodel.h"
#include <QSignalMapper>
#include "scicon.h"

#include "main.h"
#include "util.h"


#include <QTime>
#include <QTimer>
#include <QThread>
#include <QTextEdit>
#include <QKeyEvent>
#include <QUrl>
#include <QScrollBar>
#include <QStringList>
#include <QDebug>

#include <openssl/crypto.h>

#include <db_cxx.h>


#if QT_VERSION < 0x050000
#include <QUrl>
#endif

// TODO: make it possible to filter out categories (esp debug messages when implemented)
// TODO: receive errors and debug messages through ClientModel

const int CONSOLE_SCROLLBACK = 50;
const int CONSOLE_HISTORY = 50;

const QSize FONT_RANGE(4, 40);
const char fontSizeSettingsKey[] = "consoleFontSize";

const QSize ICON_SIZE(24, 24);

const int INITIAL_TRAFFIC_GRAPH_MINS = 30;

const struct {
    const char *url;
    const char *source;
} ICON_MAPPING[] = {
    {"cmd-request", ":/icons/tx_input"},
    {"cmd-reply", ":/icons/tx_output"},
    {"cmd-error", ":/icons/tx_output"},
    {"misc", ":/icons/tx_inout"},
    {NULL, NULL}
};

/* Object for executing console RPC commands in a separate thread.
*/
class RPCExecutor: public QObject
{
    Q_OBJECT
public slots:
    void start();
    void request(const QString &command);
signals:
    void reply(int category, const QString &command);
};

#include "rpcconsole.moc"

void RPCExecutor::start()
{
   // Nothing to do
}

/**
 * Split shell command line into a list of arguments. Aims to emulate \c bash and friends.
 *
 * - Arguments are delimited with whitespace
 * - Extra whitespace at the beginning and end and between arguments will be ignored
 * - Text can be "double" or 'single' quoted
 * - The backslash \c \ is used as escape character
 *   - Outside quotes, any character can be escaped
 *   - Within double quotes, only escape \c " and backslashes before a \c " or another backslash
 *   - Within single quotes, no escaping is possible and no special interpretation takes place
 *
 * @param[out]   args        Parsed arguments will be appended to this list
 * @param[in]    strCommand  Command line to split
 */
bool parseCommandLine(std::vector<std::string> &args, const std::string &strCommand)
{
    enum CmdParseState
    {
        STATE_EATING_SPACES,
        STATE_ARGUMENT,
        STATE_SINGLEQUOTED,
        STATE_DOUBLEQUOTED,
        STATE_ESCAPE_OUTER,
        STATE_ESCAPE_DOUBLEQUOTED
    } state = STATE_EATING_SPACES;
    std::string curarg;
    foreach(char ch, strCommand)
    {
        switch(state)
        {
        case STATE_ARGUMENT: // In or after argument
        case STATE_EATING_SPACES: // Handle runs of whitespace
            switch(ch)
            {
            case '"': state = STATE_DOUBLEQUOTED; break;
            case '\'': state = STATE_SINGLEQUOTED; break;
            case '\\': state = STATE_ESCAPE_OUTER; break;
            case ' ': case '\n': case '\t':
                if(state == STATE_ARGUMENT) // Space ends argument
                {
                    args.push_back(curarg);
                    curarg.clear();
                }
                state = STATE_EATING_SPACES;
                break;
            default: curarg += ch; state = STATE_ARGUMENT;
            }
            break;
        case STATE_SINGLEQUOTED: // Single-quoted string
            switch(ch)
            {
            case '\'': state = STATE_ARGUMENT; break;
            default: curarg += ch;
            }
            break;
        case STATE_DOUBLEQUOTED: // Double-quoted string
            switch(ch)
            {
            case '"': state = STATE_ARGUMENT; break;
            case '\\': state = STATE_ESCAPE_DOUBLEQUOTED; break;
            default: curarg += ch;
            }
            break;
        case STATE_ESCAPE_OUTER: // '\' outside quotes
            curarg += ch; state = STATE_ARGUMENT;
            break;
        case STATE_ESCAPE_DOUBLEQUOTED: // '\' in double-quoted text
            if(ch != '"' && ch != '\\') curarg += '\\'; // keep '\' for everything but the quote and '\' itself
            curarg += ch; state = STATE_DOUBLEQUOTED;
            break;
        }
    }
    switch(state) // final state
    {
    case STATE_EATING_SPACES:
        return true;
    case STATE_ARGUMENT:
        args.push_back(curarg);
        return true;
    default: // ERROR to end in one of the other states
        return false;
    }
}

void RPCExecutor::request(const QString &command)
{
    std::vector<std::string> args;
    if(!parseCommandLine(args, command.toStdString()))
    {
        emit reply(RPCConsole::CMD_ERROR, QString("Parse error: unbalanced ' or \""));
        return;
    }
    if(args.empty())
        return; // Nothing to do
    try
    {
        std::string strPrint;
        // Convert argument list to JSON objects in method-dependent way,
        // and pass it along with the method name to the dispatcher.
        json_spirit::Value result = tableRPC.execute(
            args[0],
            RPCConvertValues(args[0], std::vector<std::string>(args.begin() + 1, args.end())));

        // Format result reply
        if (result.type() == json_spirit::null_type)
            strPrint = "";
        else if (result.type() == json_spirit::str_type)
            strPrint = result.get_str();
        else
            strPrint = write_string(result, true);

        emit reply(RPCConsole::CMD_REPLY, QString::fromStdString(strPrint));
    }
    catch (json_spirit::Object& objError)
    {
        try // Nice formatting for standard-format error
        {
            int code = find_value(objError, "code").get_int();
            std::string message = find_value(objError, "message").get_str();
            emit reply(RPCConsole::CMD_ERROR, QString::fromStdString(message) + " (code " + QString::number(code) + ")");
        }
        catch(std::runtime_error &) // raised when converting to invalid type, i.e. missing code or message
        {   // Show raw JSON object
            emit reply(RPCConsole::CMD_ERROR, QString::fromStdString(write_string(json_spirit::Value(objError), false)));
        }
    }
    catch (std::exception& e)
    {
        emit reply(RPCConsole::CMD_ERROR, QString("Error: ") + QString::fromStdString(e.what()));
    }
}

RPCConsole::RPCConsole(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::RPCConsole),
                                          clientModel(0),
                                          historyPtr(0),
                                          peersTableContextMenu(0),
                                          consoleFontSize(0)
{
    ui->setupUi(this);

#ifndef Q_OS_MAC
    ui->openDebugLogfileButton->setIcon(QIcon(":/icons/export"));
    ui->showCLOptionsButton->setIcon(QIcon(":/icons/options"));
#endif

    // Install event filter for up and down arrow
    ui->lineEdit->installEventFilter(this);
    ui->messagesWidget->installEventFilter(this);

    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(ui->btnClearTrafficGraph, SIGNAL(clicked()), ui->trafficGraph, SLOT(clear()));

    QSettings settings;
    consoleFontSize = settings.value(fontSizeSettingsKey, QFontInfo(QFont()).pointSize()).toInt();

    connect(ui->fontBiggerButton, SIGNAL(clicked()), this, SLOT(fontBigger()));
    connect(ui->fontSmallerButton, SIGNAL(clicked()), this, SLOT(fontSmaller()));

    // set OpenSSL version label
    ui->openSSLVersion->setText(SSLeay_version(SSLEAY_VERSION));

    startExecutor();
    setTrafficGraphRange(INITIAL_TRAFFIC_GRAPH_MINS);

    ui->detailWidget->hide();
    ui->peerHeading->setText(tr("Select a peer to view detailed information."));

    clear();
}

RPCConsole::~RPCConsole()
{
    emit stopExecutor();
    delete ui;
}

bool RPCConsole::eventFilter(QObject* obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) // Special key handling
    {
        QKeyEvent *keyevt = static_cast<QKeyEvent*>(event);
        int key = keyevt->key();
        Qt::KeyboardModifiers mod = keyevt->modifiers();
        switch(key)
        {
        case Qt::Key_Up: if(obj == ui->lineEdit) { browseHistory(-1); return true; } break;
        case Qt::Key_Down: if(obj == ui->lineEdit) { browseHistory(1); return true; } break;
        case Qt::Key_PageUp: /* pass paging keys to messages widget */
        case Qt::Key_PageDown:
            if(obj == ui->lineEdit)
            {
                QApplication::postEvent(ui->messagesWidget, new QKeyEvent(*keyevt));
                return true;
            }
            break;
        default:
            // Typing in messages widget brings focus to line edit, and redirects key there
            // Exclude most combinations and keys that emit no text, except paste shortcuts
            if(obj == ui->messagesWidget && (
                  (!mod && !keyevt->text().isEmpty() && key != Qt::Key_Tab) ||
                  ((mod & Qt::ControlModifier) && key == Qt::Key_V) ||
                  ((mod & Qt::ShiftModifier) && key == Qt::Key_Insert)))
            {
                ui->lineEdit->setFocus();
                QApplication::postEvent(ui->lineEdit, new QKeyEvent(*keyevt));
                return true;
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void RPCConsole::setClientModel(ClientModel *model)
{
    clientModel = model;
    ui->trafficGraph->setClientModel(model);
    if (model && clientModel->getPeerTableModel() && clientModel->getBanTableModel())
    {
        setNumConnections(model->getNumConnections());
        // Subscribe to information, replies, messages, errors
        connect(model, SIGNAL(numConnectionsChanged(int)), this, SLOT(setNumConnections(int)));
        connect(model, SIGNAL(numBlocksChanged(int, int)), this, SLOT(setNumBlocks(int, int)));

        updateNetworkState();

        connect(model, SIGNAL(networkActiveChanged(bool)), this, SLOT(setNetworkActive(bool)));
        updateTrafficStats(model->getTotalBytesRecv(), model->getTotalBytesSent());
        connect(model, SIGNAL(bytesChanged(quint64, quint64)), this, SLOT(updateTrafficStats(quint64, quint64)));

        // set up peer table
        ui->peerWidget->setModel(model->getPeerTableModel());
        ui->peerWidget->verticalHeader()->hide();
        ui->peerWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        ui->peerWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->peerWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->peerWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->peerWidget->setColumnWidth(PeerTableModel::Address, ADDRESS_COLUMN_WIDTH);
        ui->peerWidget->setColumnWidth(PeerTableModel::Subversion, SUBVERSION_COLUMN_WIDTH);
        ui->peerWidget->horizontalHeader()->setStretchLastSection(true);

        // create peer table context menu actions
        QAction *disconnectAction = new QAction(tr("&Disconnect"), this);
        QAction *banAction1h = new QAction(tr("Ban for") + " " + tr("1 &hour"), this);
        QAction *banAction24h = new QAction(tr("Ban for") + " " + tr("1 &day"), this);
        QAction *banAction7d = new QAction(tr("Ban for") + " " + tr("1 &week"), this);
        QAction *banAction365d = new QAction(tr("Ban for") + " " + tr("1 &year"), this);

        peersTableContextMenu = new QMenu(this);
        peersTableContextMenu->addAction(disconnectAction);
        peersTableContextMenu->addAction(banAction1h);
        peersTableContextMenu->addAction(banAction24h);
        peersTableContextMenu->addAction(banAction7d);
        peersTableContextMenu->addAction(banAction365d);

        // Add a signal mapping to allow dynamic context menu arguments.
        // We need to use int (instead of int64_t), because signal mapper only supports
        // int or objects, which is okay because max bantime (1 year) is < int_max.
        QSignalMapper *signalMapper = new QSignalMapper(this);
        signalMapper->setMapping(banAction1h, 60 * 60);
        signalMapper->setMapping(banAction24h, 60 * 60 * 24);
        signalMapper->setMapping(banAction7d, 60 * 60 * 24 * 7);
        signalMapper->setMapping(banAction365d, 60 * 60 * 24 * 365);
        connect(banAction1h, SIGNAL(triggered()), signalMapper, SLOT(map()));
        connect(banAction24h, SIGNAL(triggered()), signalMapper, SLOT(map()));
        connect(banAction7d, SIGNAL(triggered()), signalMapper, SLOT(map()));
        connect(banAction365d, SIGNAL(triggered()), signalMapper, SLOT(map()));
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(banSelectedNode(int)));

        // peer table context menu signals
        connect(ui->peerWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showPeersTableContextMenu(const QPoint &)));
        connect(disconnectAction, SIGNAL(triggered()), this, SLOT(disconnectSelectedNode()));

        // connect the peerWidget selection model to our peerSelected() handler
        connect(ui->peerWidget->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
                this, SLOT(peerSelected(const QItemSelection &, const QItemSelection &)));
        // peer table signal handling - update peer details when new nodes are added to the model
        connect(model->getPeerTableModel(), SIGNAL(layoutChanged()), this, SLOT(peerLayoutChanged()));

        // set up ban table
        ui->banlistWidget->setModel(model->getBanTableModel());
        ui->banlistWidget->verticalHeader()->hide();
        ui->banlistWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->banlistWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->banlistWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->banlistWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        ui->banlistWidget->setColumnWidth(BanTableModel::Address, BANSUBNET_COLUMN_WIDTH);
        ui->banlistWidget->setColumnWidth(BanTableModel::Bantime, BANTIME_COLUMN_WIDTH);
        ui->banlistWidget->horizontalHeader()->setStretchLastSection(true);

        // create ban table context menu action
        QAction *unbanAction = new QAction(tr("&Unban"), this);
        // create ban table context menu
        banTableContextMenu = new QMenu(this);
        banTableContextMenu->addAction(unbanAction);

        // ban table context menu signals
        connect(ui->banlistWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showBanTableContextMenu(const QPoint &)));
        connect(unbanAction, SIGNAL(triggered()), this, SLOT(unbanSelectedNode()));

        // ban table signal handling - clear peer details when clicking a peer in the ban table
        connect(ui->banlistWidget, SIGNAL(clicked(const QModelIndex &)), this, SLOT(clearSelectedNode()));
        // ban table signal handling - ensure ban table is shown or hidden (if empty)
        connect(model->getBanTableModel(), SIGNAL(layoutChanged()), this, SLOT(showOrHideBanTableIfRequired()));
        showOrHideBanTableIfRequired();

        // Provide initial values
        ui->clientVersion->setText(model->formatFullVersion());
        ui->clientName->setText(model->clientName());
        ui->buildDate->setText(model->formatBuildDate());
        ui->startupTime->setText(model->formatClientStartupTime());

        ui->isTestNet->setChecked(model->isTestNet());

        setNumBlocks(model->getNumBlocks(), model->getNumBlocksOfPeers());

        //Setup autocomplete and attach it
        QStringList wordList;
        std::vector<std::string> commandList = tableRPC.listCommands();
        for (size_t i = 0; i < commandList.size(); ++i)
        {
            wordList << commandList[i].c_str();
            wordList << ("help " + commandList[i]).c_str();
        }
        wordList.sort();

        autoCompleter = new QCompleter(wordList, this);
        autoCompleter->setModelSorting(QCompleter::CaseSensitivelySortedModel);
        ui->lineEdit->setCompleter(autoCompleter);
        autoCompleter->popup()->installEventFilter(this);
    }
    if (!model)
    {
        // Client model is being set to 0, this means shutdown() is about to be called.
        // Make sure we clean up the executor thread
        Q_EMIT stopExecutor();
        thread.wait();
    }
}


static QString categoryClass(int category)
{
    switch(category)
    {
    case RPCConsole::CMD_REQUEST:  return "cmd-request"; break;
    case RPCConsole::CMD_REPLY:    return "cmd-reply"; break;
    case RPCConsole::CMD_ERROR:    return "cmd-error"; break;
    default:                       return "misc";
    }
}

void RPCConsole::clear(bool clearHistory)
{
    ui->messagesWidget->clear();
    if(clearHistory)
    {
        history.clear();
        historyPtr = 0;
    }
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();

    // Add smoothly scaled icon images.
    // (when using width/height on an img, Qt uses nearest instead of linear interpolation)
    for(int i=0; ICON_MAPPING[i].url; ++i)
    {
        ui->messagesWidget->document()->addResource(
                    QTextDocument::ImageResource,
                    QUrl(ICON_MAPPING[i].url),
                    QImage(ICON_MAPPING[i].source).scaled(ICON_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    // Set default style sheet
    ui->messagesWidget->document()->setDefaultStyleSheet(
        QString(
                "table { }"
                "td.time { color: #808080; font-size: %1; padding-top: 3px; } "
                "td.message { font-family: Monospace; font-size: %1; } "
                "td.cmd-request { color: #ffff99; } "
                "td.cmd-error { color: red; } "
                "b { color: #ffff99; } "
       ).arg( QString("%1pt").arg(consoleFontSize))
    );

    message(CMD_REPLY, (tr("Welcome to the DeepOnion RPC console.") + "<br>" +
                        tr("Use up and down arrows to navigate history, and <b>Ctrl-L</b> to clear screen.") + "<br>" +
                        tr("Type <b>help</b> for an overview of available commands.")), true);
}


void RPCConsole::fontBigger()
{
    setFontSize(consoleFontSize+1);
}

void RPCConsole::fontSmaller()
{
    setFontSize(consoleFontSize-1);
}

void RPCConsole::setFontSize(int newSize)
{
    //don't allow a insane font size
    if (newSize < FONT_RANGE.width() || newSize > FONT_RANGE.height())
        return;

    // temp. store the console content
    QString str = ui->messagesWidget->toHtml();

    // replace font tags size in current content
    str.replace(QString("font-size:%1pt").arg(consoleFontSize), QString("font-size:%1pt").arg(newSize));

    // store the new font size
    consoleFontSize = newSize;
    settings.setValue(fontSizeSettingsKey, consoleFontSize);

    // clear console (reset icon sizes, default stylesheet) and re-add the content
    float oldPosFactor = 1.0 / ui->messagesWidget->verticalScrollBar()->maximum() * ui->messagesWidget->verticalScrollBar()->value();
    clear(false);
    ui->messagesWidget->setHtml(str);
    ui->messagesWidget->verticalScrollBar()->setValue(oldPosFactor * ui->messagesWidget->verticalScrollBar()->maximum());
}

void RPCConsole::message(int category, const QString &message, bool html)
{
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    QString out;
    out += "<table><tr><td class=\"time\" width=\"65\">" + timeString + "</td>";
    out += "<td class=\"icon\" width=\"32\"><img src=\"" + categoryClass(category) + "\"></td>";
    out += "<td class=\"message " + categoryClass(category) + "\" valign=\"middle\">";
    if(html)
        out += message;
    else
        out += GUIUtil::HtmlEscape(message, true);
    out += "</td></tr></table>";
    ui->messagesWidget->append(out);
}

void RPCConsole::setNumConnections(int count)
{
    if (!clientModel)
        return;

    updateNetworkState();
}

void RPCConsole::setNetworkActive(bool networkActive)
{
    updateNetworkState();
}

void RPCConsole::updateNetworkState()
{
    QString connections = QString::number(clientModel->getNumConnections()) + " (";
    connections += tr("In:") + " " + QString::number(clientModel->getNumConnections(CONNECTIONS_IN)) + " / ";
    connections += tr("Out:") + " " + QString::number(clientModel->getNumConnections(CONNECTIONS_OUT)) + ")";

    ui->numberOfConnections->setText(connections);
}

void RPCConsole::setNumBlocks(int count, int countOfPeers)
{
    ui->numberOfBlocks->setText(QString::number(count));
    ui->totalBlocks->setText(QString::number(countOfPeers));
    if(clientModel)
    {
        // If there is no current number available display N/A instead of 0, which can't ever be true
        ui->totalBlocks->setText(clientModel->getNumBlocksOfPeers() == 0 ? tr("N/A") : QString::number(clientModel->getNumBlocksOfPeers()));
        ui->lastBlockTime->setText(clientModel->getLastBlockDate().toString());
    }
}

void RPCConsole::on_lineEdit_returnPressed()
{
    QString cmd = ui->lineEdit->text();
    ui->lineEdit->clear();

    if(!cmd.isEmpty())
    {
        message(CMD_REQUEST, cmd);
        emit cmdRequest(cmd);
        // Truncate history from current position
        history.erase(history.begin() + historyPtr, history.end());
        // Append command to history
        history.append(cmd);
        // Enforce maximum history size
        while(history.size() > CONSOLE_HISTORY)
            history.removeFirst();
        // Set pointer to end of history
        historyPtr = history.size();
        // Scroll console view to end
        scrollToEnd();
    }
}

void RPCConsole::browseHistory(int offset)
{
    historyPtr += offset;
    if(historyPtr < 0)
        historyPtr = 0;
    if(historyPtr > history.size())
        historyPtr = history.size();
    QString cmd;
    if(historyPtr < history.size())
        cmd = history.at(historyPtr);
    ui->lineEdit->setText(cmd);
}

void RPCConsole::startExecutor()
{
    RPCExecutor *executor = new RPCExecutor();
    executor->moveToThread(&thread);

    // Replies from executor object must go to this object
    connect(executor, SIGNAL(reply(int, QString)), this, SLOT(message(int, QString)));
    // Requests from this object must go to executor
    connect(this, SIGNAL(cmdRequest(QString)), executor, SLOT(request(QString)));

    // On stopExecutor signal
    // - quit the Qt event loop in the execution thread
    connect(this, SIGNAL(stopExecutor()), &thread, SLOT(quit()));
    // - queue executor for deletion (in execution thread)
    connect(&thread, SIGNAL(finished()), executor, SLOT(deleteLater()), Qt::DirectConnection);

    // Default implementation of QThread::run() simply spins up an event loop in the thread,
    // which is what we want.
    thread.start();
}

void RPCConsole::on_tabWidget_currentChanged(int index)
{
    if(ui->tabWidget->widget(index) == ui->tab_console)
    {
        ui->lineEdit->setFocus();
    }
}

void RPCConsole::on_openDebugLogfileButton_clicked()
{
    GUIUtil::openDebugLogfile();
}

void RPCConsole::on_showMeDetailsButton_clicked()
{
    BlockchainDialog dlg;
    dlg.exec();
}

void RPCConsole::scrollToEnd()
{
    QScrollBar *scrollbar = ui->messagesWidget->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void RPCConsole::on_sldGraphRange_valueChanged(int value)
{
    const int multiplier = 5; // each position on the slider represents 5 min
    int mins = value * multiplier;
    setTrafficGraphRange(mins);
}

void RPCConsole::showPeersTableContextMenu(const QPoint &point)
{
    QModelIndex index = ui->peerWidget->indexAt(point);
    if (index.isValid())
        peersTableContextMenu->exec(QCursor::pos());
}

void RPCConsole::showBanTableContextMenu(const QPoint &point)
{
    QModelIndex index = ui->banlistWidget->indexAt(point);
    if (index.isValid())
        banTableContextMenu->exec(QCursor::pos());
}

void RPCConsole::showOrHideBanTableIfRequired()
{
    if (!clientModel)
        return;


    bool visible = clientModel->getBanTableModel()->shouldShow();
    ui->banlistWidget->setVisible(visible);
    ui->banHeading->setVisible(visible);
}
void RPCConsole::clearSelectedNode()
{
    ui->peerWidget->selectionModel()->clearSelection();
    cachedNodeid = -1;
    ui->detailWidget->hide();
    ui->peerHeading->setText(tr("Select a peer to view detailed information."));
}

QString RPCConsole::FormatBytes(quint64 bytes)
{
    return QString::fromStdString(bytesReadable(bytes));
}

void RPCConsole::setTrafficGraphRange(int mins)
{
    ui->trafficGraph->setGraphRangeMins(mins);
    ui->lblGraphRange->setText(GUIUtil::formatDurationStr(mins * 60));
}

void RPCConsole::updateTrafficStats(quint64 totalBytesIn, quint64 totalBytesOut)
{
    ui->lblBytesIn->setText(FormatBytes(totalBytesIn));
    ui->lblBytesOut->setText(FormatBytes(totalBytesOut));
}

void RPCConsole::peerSelected(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    if (!clientModel || !clientModel->getPeerTableModel() || selected.indexes().isEmpty())
        return;

    const CNodeCombinedStats *stats = clientModel->getPeerTableModel()->getNodeStats(selected.indexes().first().row());
    if (stats)
        updateNodeDetail(stats);
}

void RPCConsole::peerLayoutChanged()
{
    if (!clientModel || !clientModel->getPeerTableModel())
        return;

    const CNodeCombinedStats *stats = NULL;
    bool fUnselect = false;
    bool fReselect = false;

    if (cachedNodeid == -1) // no node selected yet
        return;

    // find the currently selected row
    int selectedRow;
    QModelIndexList selectedModelIndex = ui->peerWidget->selectionModel()->selectedIndexes();
    if (selectedModelIndex.isEmpty())
        selectedRow = -1;
    else
        selectedRow = selectedModelIndex.first().row();

    // check if our detail node has a row in the table (it may not necessarily
    // be at selectedRow since its position can change after a layout change)
    int detailNodeRow = clientModel->getPeerTableModel()->getRowByNodeId(cachedNodeid);

    if (detailNodeRow < 0)
    {
        // detail node dissapeared from table (node disconnected)
        fUnselect = true;
        cachedNodeid = -1;
        ui->detailWidget->hide();
        ui->peerHeading->setText(tr("Select a peer to view detailed information."));
    }
    else
    {
        if (detailNodeRow != selectedRow)
        {
            // detail node moved position
            fUnselect = true;
            fReselect = true;
        }

        // get fresh stats on the detail node.
        stats = clientModel->getPeerTableModel()->getNodeStats(detailNodeRow);
    }

    if (fUnselect && selectedRow >= 0)
    {
        clearSelectedNode();
    }

    if (fReselect)
    {
        ui->peerWidget->selectRow(detailNodeRow);
    }

    if (stats)
        updateNodeDetail(stats);
}

void RPCConsole::updateNodeDetail(const CNodeCombinedStats *stats)
{
    // Update cached nodeid
    cachedNodeid = stats->nodeStats.nodeid;

    // update the detail ui with latest node information
    QString peerAddrDetails(QString::fromStdString(stats->nodeStats.addrName));
    if (!stats->nodeStats.addrLocal.empty())
        peerAddrDetails += "<br />" + tr("via %1").arg(QString::fromStdString(stats->nodeStats.addrLocal));
    ui->peerHeading->setText(peerAddrDetails);
    ui->peerServices->setText(GUIUtil::formatServicesStr(stats->nodeStats.nServices));
    ui->peerLastSend->setText(stats->nodeStats.nLastSend ? GUIUtil::formatDurationStr(GetTime() - stats->nodeStats.nLastSend) : tr("never"));
    ui->peerLastRecv->setText(stats->nodeStats.nLastRecv ? GUIUtil::formatDurationStr(GetTime() - stats->nodeStats.nLastRecv) : tr("never"));
    ui->peerBytesSent->setText(FormatBytes(stats->nodeStats.nSendBytes));
    ui->peerBytesRecv->setText(FormatBytes(stats->nodeStats.nRecvBytes));
    ui->peerConnTime->setText(GUIUtil::formatDurationStr(GetTime() - stats->nodeStats.nTimeConnected));
    ui->peerPingTime->setText(GUIUtil::formatPingTime(stats->nodeStats.dPingTime));
    ui->timeoffset->setText(GUIUtil::formatTimeOffset(stats->nodeStats.nTimeOffset));
    ui->peerVersion->setText(QString("%1").arg(stats->nodeStats.nVersion));
    ui->peerSubversion->setText(QString::fromStdString(stats->nodeStats.strSubVer));
    ui->peerDirection->setText(stats->nodeStats.fInbound ? tr("Inbound") : tr("Outbound"));
    ui->peerHeight->setText(QString("%1").arg(stats->nodeStats.nStartingHeight));

    // This check fails for example if the lock was busy and
    // nodeStateStats couldn't be fetched.
    if (stats->fNodeStateStatsAvailable)
    {
        // // Ban score is init to 0
        ui->peerBanScore->setText(QString("%1").arg(stats->nodeStateStats.nMisbehavior));

        // // Sync height is init to -1
        // if (stats->nodeStateStats.nSyncHeight > -1)
        //     ui->peerSyncHeight->setText(QString("%1").arg(stats->nodeStateStats.nSyncHeight));
        // else
        //     ui->peerSyncHeight->setText(tr("Unknown"));
    }
    // else
    // {
    //     ui->peerBanScore->setText(tr("Fetching..."));
    //     ui->peerSyncHeight->setText(tr("Fetching..."));
    // }

    ui->detailWidget->show();
}

void RPCConsole::disconnectSelectedNode()
{
    // Get currently selected peer address
    QString strNode = GUIUtil::getEntryData(ui->peerWidget, 0, PeerTableModel::Address);
    // Find the node, disconnect it and clear the selected node
    if (CNode *bannedNode = FindNode(strNode.toStdString()))
    {
        bannedNode->fDisconnect = true;
        clearSelectedNode();
    }
}

void RPCConsole::banSelectedNode(int bantime)
{
    if (!clientModel)
        return;
    
    // Get current selected peer address
    QString strNode = GUIUtil::getEntryData(ui->peerWidget, 0, PeerTableModel::Address);
    // Find possible node, ban and remove it
    if (FindNode(strNode.toStdString()))
    {
        std::string nStr = strNode.toStdString();
        std::string addr;
        int port = 0;
        SplitHostPort(nStr, port, addr);

        CNode::Ban(CNetAddr(addr), bantime);

        clearSelectedNode();
        clientModel->getBanTableModel()->refresh();
    }
}

void RPCConsole::unbanSelectedNode()
{
    if (!clientModel)
        return;

    // Get currently selected ban address
    CNode::Unban(CNetAddr(GUIUtil::getEntryData(ui->banlistWidget, 0, BanTableModel::Address).toStdString()));
    clientModel->getBanTableModel()->refresh();
}

void RPCConsole::showConfEditor()
{
    GUIUtil::openConfigfile();
}

void RPCConsole::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void RPCConsole::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    if (!clientModel || !clientModel->getPeerTableModel())
        return;

    // start PeerTableModel auto refresh
    clientModel->getPeerTableModel()->startAutoRefresh();
}

void RPCConsole::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);

    if (!clientModel || !clientModel->getPeerTableModel())
        return;

    // stop PeerTableModel auto refresh
    clientModel->getPeerTableModel()->stopAutoRefresh();
}

void RPCConsole::on_showCLOptionsButton_clicked()
{
    GUIUtil::HelpMessageBox help;
    help.exec();
}
