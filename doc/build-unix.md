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

    cd deeponion/src
    sudo rm key.h
    cp ../contrib/ubuntu18/key.h .
    cd .. && make

**Ubuntu 14.04**

If you have problems with boost libraries visit [this link](https://github.com/deeponion/deeponion/issues/63#issuecomment-365329304) for a possible solution.

Another tested solution is the one for Debian 8. See below for more details. 

**Debian 9**

It has been reported that under Debian 9 the installation of *libssl1.1-dev* leads to compilation errors.

If you experience such issues, put *libssl1.0-dev* into your install list, or see [seperate build instructions](https://github.com/deeponion/deeponion/blob/raspberry/doc/build-debian-9.md).

**Debian 8**

It has been reported the following problem when one compiles the wallet on Debian 8:

    make[1]: Entering directory ‘/home/deeponion/deeponion/src’
      CXXLD    DeepOniond
    libbitcoin_wallet.a(libbitcoin_wallet_a-walletdb.o): In function `copy_file’:
    /usr/include/boost/filesystem/operations.hpp:381: undefined reference to `boost::filesystem::detail::copy_file(boost::filesystem::path const&, boost::filesystem::path const&, boost::filesystem::copy_option, boost::system::error_code*)'
    collect2: error: ld returned 1 exit status
    Makefile:2224: recipe for target ‘DeepOniond’ failed
    make[1]: *** [DeepOniond] Error 1
    make[1]: Leaving directory ‘/home/deeponion/deeponion/src’
    Makefile:531: recipe for target ‘all-recursive’ failed
    make: *** [all-recursive] Error 1

To fix it one has to edit the file `/src/walletdb.h` and add at the top (before #include "db.h") the following: #define `BOOST_NO_CXX11_SCOPED_ENUMS`

These are the first lines of that file modified:

    // Copyright (c) 2009-2010 Satoshi Nakamoto
    // Copyright (c) 2009-2012 The Bitcoin developers
    // Distributed under the MIT/X11 software license, see the accompanying
    // file COPYING or http://www.opensource.org/licenses/mit-license.php.
    #ifndef BITCOIN_WALLETDB_H
    #define BITCOIN_WALLETDB_H

    #define BOOST_NO_CXX11_SCOPED_ENUMS

    #include "db.h"
    #include "base58.h"
    #include "stealth.h"

    class CKeyPool;
    class CAccount;
    class CAccountingEntry;

Another option (untested) could be execute `./configure` with the following flags:

    ./configure --with-incompatible-bdb CXXFLAGS=“-DBOOST_NO_CXX11_SCOPED_ENUMS”


**Centos**

Use yum instead of apt-get. 

In some cases you need to install devel version. Such as
	yum install libcap-devel libseccomp-developers
	
You may also need to patch `/src/walletdb.h` as listed above in Debian 8 section.
