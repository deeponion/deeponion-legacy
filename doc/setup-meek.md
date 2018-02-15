## Meek Obfuscation Layer Setup

**Meek** is another [pluggable transport](https://trac.torproject.org/projects/tor/wiki/doc/PluggableTransports) supported by DeepOnion which relays the traffic through a third-party server, for example a [CDN](https://en.wikipedia.org/wiki/Content_delivery_network). This technique uses a trick called [domain fronting](https://www.bamsoftware.com/papers/fronting/) to communicate with a Tor relay while appearing to communicate with another domain.

### Prerequisites

If you're on Windows a Tor-Browser installation is **mandatory** as we will be using the **meek-client.exe** from the installation directory. Please, [download the installation package](https://www.torproject.org/projects/torbrowser.html.en) for your system and run the installer.

Under Windows the meek-client executable is located at 

`YOUR_TOR_BROWSER_ROOT\Browser\TorBrowser\Tor\PluggableTransports`

Under Linux the installation of Tor-Broweser is not needed. [meek-client](https://launchpad.net/~hda-me/+archive/ubuntu/meek) can be installed separately by executing below commands:

```
sudo add-apt-repository ppa:hda-me/meek
sudo apt-get update
sudo apt-get install meek-client
```

The executable will be located under `/usr/bin/meek-client`. If your Linux system installs packages in a different folder, query the location by executing `which meek-client`. 

### Configuration

Open your *DeepOnion.conf* and enter below parameters to activate **meek** at the Wallet UI or daemon startup.

```
torplugin=meek
torpluginpath=MEEK_CLIENT_EXE_PATH (e.g. c:\bin\meek-client.exe or /usr/bin/meek-client)
```

### Location of the meek-client executable

On Windows the full path to `meek-client.exe` depends on your [Tor-Browser](https://www.torproject.org/projects/torbrowser.html.en) path. Do not attempt to start your Wallet UI or daemon without having provided the full path to *meek-client*. 

This is an example of a location of *meek-client.exe* when Tor-Browser was installed under `C:\bin`:

![meek-location-win](https://img3.picload.org/image/ddwawdiw/meek_client.png)

It's also allowed to copy *meek-client.exe* to another location, for example the folder of your Wallet UI. In this case you have to take care of providing the correct path.

On Linux and Mac you can get the location of meek-client by executing `which meek-client` in the console.

### Managing Bridges

As *meek-client* heavily depends on available Bridges it is very important to keep an eye on them. Be always up-to-date regarding [available front domains](https://trac.torproject.org/projects/tor/wiki/doc/meek).

You should also look into *extension-override.js* that is located under *Browser\TorBrowser\Data\Browser\profile.default\preferences* in your Tor-Browser path. Open this file and scroll down until you see entries that begin with `extensions.torlauncher.default_bridge.meek`.

![extension-override.js](https://img3.picload.org/image/ddwawala/extension_override.png)

Copy the contents from lines that begin with `meek 0.0.` and append the keyword `Bridge` to both of them. They should now look like this:

```
Bridge meek 0.0.2.0:2 B9E7141C594AF25699E0079C1F0146F409495296 url=https://d2cly7j4zqgua7.cloudfront.net/ front=a0.awsstatic.com
Bridge meek 0.0.2.0:3 97700DFE9F483596DDA6264C4D7DF7641E1E39CE url=https://meek.azureedge.net/ front=ajax.aspnetcdn.com
```

Insert those lines into your *torrc* which is located under:

* %APPDATA%/Roaming/DeepOnion/tor (Windows)

![appdata-torrc](https://camo.githubusercontent.com/88e2eeb4a949d4f5bbc9fe86d3c1c943de03dc9c/68747470733a2f2f696d67322e7069636c6f61642e6f72672f696d6167652f64647063616772612f746f7272635f706174682e706e67)

* ~/.DeepOnion/tor (Linux)
* ~/Library/Application Support/DeepOnion/tor (Mac)

Under Windows you must take care of **not** saving this file with default extension appended to it (usually *.txt). One good way to avoid this problem is to edit the file with a powerful text editor like [Nodepad++](https://notepad-plus-plus.org/download/v7.5.4.html) and to select *All types* option on saving.

![save-torrc](https://img3.picload.org/image/ddwaworl/save_torrc.png)

### Running DeepOnion with Meek

Open your *tor.log* which is located under the same folder where your *torrc* is. After a few moments you should see an output similar to this:

![meek_tor-log](https://img2.picload.org/image/ddwogdri/meek_log_tor.png)

### Potential Issues

* During our tests *on Windows* we experienced issues when running the Wallet UI with multiple Bridge entries in *torrc*. The problems didn't show up with configurations containing only a **single** active Bridge entry.
* After closing the Wallet UI on Windows you'll have to close the running meek-client.exe manually (via [TaskManager](https://en.wikipedia.org/wiki/Task_Manager_(Windows)) for example)
* If your Bridge is blocked, as it often happens in China, please get additional information from below websites. The front servers can change at any time and it's your responsibility to be up-to-date.


[In China, Meek-azure and Meek-amazon can not be used, the following is the log, how can we use Meek?](https://tor.stackexchange.com/questions/14170/in-china-meek-azure-and-meek-amazon-can-not-be-used-the-following-is-the-log)

[What to do if meek gets blocked?](https://lists.torproject.org/pipermail/tor-talk/2015-January/036410.html)

A list of **censored** *cloudfront* domains can be found [here](https://en.greatfire.org/search/all/cloudfront.net).
