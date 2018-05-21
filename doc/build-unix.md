### UNIX BUILD NOTES

*The following are commands needed to build on ubuntu/debian from scratch (use sudo if you are not root). It is verified with ubuntu 16.04 and 17.04.

#### Libraries 

First get the dependencies:

```
apt-get update
apt-get upgrade
apt-get install build-essential libtool autotools-dev autoconf automake pkg-config libssl-dev libboost-all-dev bsdmainutils
apt-get install libqrencode-dev libminiupnpc-dev libevent-dev libcap-dev libseccomp-dev git
```
```
apt-get install software-properties-common
add-apt-repository ppa:bitcoin/bitcoin
apt-get update
apt-get install libdb4.8-dev libdb4.8++-dev
```

#### GUI Version

If you want to build GUI version, do this, otherwise you can skip this step:

```
apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
```
#### DeepOnion Source

Then get deeponion source:

`git clone --recursive https://github.com/deeponion/deeponion.git`

#### Autotools

Build with autotools:

    cd deeponion
    ./autogen.sh
    ./configure --with-gui=qt5    (if you want to build daemon, use --without-gui)
    make
    
#### Issues

**Ubuntu 18.04**

For ECDSA_SIG related errors, change the key.h file for the [Raspberry Pi branch](https://github.com/deeponion/deeponion/blob/raspberry/src/key.h) version then re-build:

sudo apt install curl
cd ~/deeponion/src
sudo rm key.h
wget curl -o key.h https://raw.githubusercontent.com/deeponion/deeponion/raspberry/src/key.h
cd .. && make

**Ubuntu 14.04**

If you have problems with boost libraries visit [this link](https://github.com/deeponion/deeponion/issues/63#issuecomment-365329304) for a possible solution.

**Debian 9**

It has been reported that under Debian 9 the installation of *libssl1.1-dev* leads to compilation errors. 

If you experience such issues, put *libssl1.0-dev* into your install list, or see [seperate build instructions](https://github.com/deeponion/deeponion/blob/raspberry/doc/build-debian-9.md).
