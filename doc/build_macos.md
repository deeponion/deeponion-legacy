Open a *Terminal*.

1.  *Clone the github tree to get the source code and checkout the Mac branch*

```
git clone --recursive https://github.com/deeponion/deeponion.git
cd deeponion
git checkout macos
```

2.  *Download and install Brew for Mac* (https://brew.sh)

3.  *Install dependencies with Brew*

```
brew install autoconf
brew install automake
brew install pkg-config
brew install protobuf
brew install boost@1.57 --cc=clang 
brew link boost@1.57 --force
brew install berkeley-db@4 
brew link berkeley-db@4 --force
brew install openssl 
brew install miniupnpc
brew install libevent
brew install qt5  [only use if building the Wallet UI]
brew link qt5 --force
brew install qrencode [only use if building the Wallet UI]
```
3.  *Build DeepOnion*

```
cd deeponion
./autogen.sh
./configure --with-gui=qt5 --disable-tests [or use --without-gui if only building the daemon]
make
```

4. *Outputs*

The daemon will be located under *src/DeepOniond*, the Wallet UI under *src/qt/DeepOnion-qt*.

You can now start them directly (either the daemon or the wallet but never both of them at the same time!), or you can first copy them somewhere else and then start them by typing in their respective names. The apps will automatically find your default DeepOnion directory (if you already have one).

5. *Creating a DMG*

After a successful compilation you have the option to create a DMG for easier macOS deployment. 

For this type: `sudo make deploy` in the Terminal and enter the **administrator password** when asked. 

Your Mac will now start to create several files and also open a Window with DeepOnion icons in it. **Do not interfere with this process!** Let it finish its work. After a successful DMG creation you'll get the **DeepOnion-Qt.dmg** file in `deeponion` directory. Use this file by double clicking on it and installing the Wallet in the Applications path.
