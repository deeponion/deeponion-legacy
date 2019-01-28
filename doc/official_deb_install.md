## Tails
This guide provides instructions of how to install the DeepOnion-QT and DeepOniond application on your Tails system in a persistent way.

Although possible, it is not recommended to use a wallet on Tails without a persistent volume. There is high risk of losing your ONION's if you do.

Boot Tails with your persistent volume unlocked and ensure you have set an administrator password.

Install persistent sources
```
sudo install -d -m 755 /live/persistence/TailsData_unlocked/apt-sources.list.d
```
Add the sources directory to the
persistence
```
echo "/etc/apt/sources.list.d  source=apt-sources.list.d,link" | sudo tee --append /live/persistence/TailsData_unlocked/persistence.conf
```
Add our sources to the persistent sources list.
```
echo "deb tor+http://ppa.launchpad.net/bitcoin/bitcoin/ubuntu xenial main"  | sudo tee --append /live/persistence/TailsData_unlocked/apt-sources.list.d/deeponion.list
echo "deb [arch=amd64] tor+http://ppa.deeponion.org.uk/debian stretch main"  | sudo tee --append /live/persistence/TailsData_unlocked/apt-sources.list.d/deeponion.list
sudo chown root:root /live/persistence/TailsData_unlocked/apt-sources.list.d/deeponion.list
sudo chmod 644 /live/persistence/TailsData_unlocked/apt-sources.list.d/deeponion.list
sudo ln -s /live/persistence/TailsData_unlocked/apt-sources.list.d/deeponion.list /etc/apt/sources.list.d/deeponion.list
```
Ensure DeepOnion is reinstalled each time Tails boots
```
echo "deeponion-qt" | sudo tee --append /live/persistence/TailsData_unlocked/live-additional-software.conf
echo "deeponiond" | sudo tee --append /live/persistence/TailsData_unlocked/live-additional-software.conf
```
Create the persistent DeepOnion data directory
```
mkdir -p /home/amnesia/Persistent/.DeepOnion
```
Install the GPG keys
```
wget http://ppa.deeponion.org.uk/bitcoin.gpg
sudo apt-key add bitcoin.gpg
wget http://ppa.deeponion.org.uk/pgp.key
sudo apt-key add pgp.key
```
Install the software
```
sudo apt-get update
sudo apt-get install deeponion-qt deeponiond
```
The below setup should be done on each boot.
Configure the firewall to allow DeepOnion to connect. To do this add this into /etc/ferm/ferm.conf
```
# White-list access to DeepOnion
daddr 127.0.0.1 proto tcp syn dport 9081 {
  mod owner uid-owner \$amnesia_uid ACCEPT;
}
```
Re run the firewall config.
```
sudo ferm /etc/ferm/ferm.conf
```
Launch DeepOnion-QT
```
torsocks DeepOnion-qt -datadir=/home/amnesia/Persistent/.DeepOnion
```
Alternatively, to use the menu icon modify the /usr/share/applications/DeepOnion-qt.desktop to look like this.
```
[Desktop Entry]
Name=DeepOnion Qt
Comment=The GUI version of the DeepOnion wallet.
Exec=torsocks DeepOnion-qt -datadir=/home/amnesia/Persistent/.DeepOnion
Icon=DeepOnion
Type=Application
Categories=Utility;
```
## Debian - Stretch AMD64

Download our GPG public key
```
wget http://ppa.deeponion.org.uk/pgp.key
sudo apt-key add pgp.key
```
Download the bitcoin GPG public key
```
wget http://ppa.deeponion.org.uk/bitcoin.gpg
sudo apt-key add bitcoin.gpg
```
Add the sources
```
sudo echo "deb http://ppa.launchpad.net/bitcoin/bitcoin/ubuntu xenial main"  | sudo tee --append /etc/apt/sources.list.d/deeponion.list
sudo echo "deb [arch=amd64] http://ppa.deeponion.org.uk/debian stretch main"  | sudo tee --append /etc/apt/sources.list.d/deeponion.list
```
Install DeepOnion QT and/or Daemon
```
sudo apt-get update
sudo apt-get install deeponion-qt deeponiond
```
## Ubuntu - Bionic (18.04) AMD64

Download our GPG public key
```
wget http://ppa.deeponion.org.uk/pgp.key
sudo apt-key add pgp.key
```
Add the sources
```
sudo echo "deb [arch=amd64] http://ppa.deeponion.org.uk/ubuntu bionic main"  | sudo tee --append /etc/apt/sources.list.d/deeponion.list
```
Add the bitcoin PPA
```
sudo add-apt-repository ppa:bitcoin/bitcoin -y
```
Install DeepOnion QT and/or Daemon
```
sudo apt-get update
sudo apt-get install deeponion-qt deeponiond
```
