### OBFS4 Proxy Setup

To run the Wallet with obfs4 enabled one must install the *obfs4proxy* [package](https://launchpad.net/ubuntu/+source/obfs4proxy) first. Also don't forget **to close your Wallet or daemon** before starting to change configuration files below.

#### Install obfs4proxy (Ubuntu, Debian)

```shell
sudo apt-get install obfs4proxy
```

#### Find available Bridges

Visit this [website](https://bridges.torproject.org/bridges) to get a list of Bridges which you'll insert into the *torrc* file under your *datadir*.

#### Edit tor configuration file

Your *datadir* depends on the OS you're using. Possible locations of the *torrc* are:

* Windows - %APPDATA%/DeepOnion/tor
* Linux - ~/.DeepOnion/tor
* Mac -  ~/Library/Application Support/DeepOnion/tor

Open *torrc* and remove any lines that begin with *Bridge*. Now add the bridges you got from the above website with the keyword *Bridge* prepended.

Here's an example:

```
Bridge 80.92.79.70:80 312D64274C29156005843EECB19C6865FA3CC10C
Bridge 52.19.30.6:8443 FC5D6558344479BBB10E8638CC8CEB8BA6E32DAD
Bridge 178.63.28.14:443 88CB40E536DD6F6775626E6A3BCC5D9C0B7BAFEA
```

Start your wallet, or daemon if running *headless*, and trace your tor's *logfile* with:

```
tail -f YOUR_DATADIR/tor/tor.log
```

You should see entries similar to those below:

```
Jan 28 20:31:14.000 [notice] Bootstrapped 0%: Starting
Jan 28 20:31:15.000 [notice] Starting with guard context "bridges"
Jan 28 20:31:15.000 [notice] new bridge descriptor 'piratepartei0' (cached): $312D64274C29156005843EECB19C6865FA3CC10C~piratepartei0 at 80.92.79.70
Jan 28 20:31:15.000 [notice] Bridge 'dax' has both an IPv4 and an IPv6 address.  Will prefer using its IPv4 address (178.63.28.14:443) based on the configured Br
idge address.
Jan 28 20:31:15.000 [notice] new bridge descriptor 'dax' (cached): $88CB40E536DD6F6775626E6A3BCC5D9C0B7BAFEA~dax at 178.63.28.14
Jan 28 20:31:15.000 [notice] Bootstrapped 80%: Connecting to the Tor network
Jan 28 20:31:15.000 [notice] Bootstrapped 85%: Finishing handshake with first hop
Jan 28 20:31:16.000 [notice] Bootstrapped 90%: Establishing a Tor circuit
Jan 28 20:31:16.000 [notice] Tor has successfully opened a circuit. Looks like client functionality is working.
Jan 28 20:31:16.000 [notice] Bootstrapped 100%: Done

```