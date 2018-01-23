## HOWTO - Build the DeepOnion Wallet under Windows


Building the DeepOnion Wallet is no easy task as it comprises of several components, libraries and tools which have to be stored, maintained and executed in certain order. This HOWTO aims to provide a detailed description, so that developers and power-users can easily solve all of the tasks and avoid several, often nasty, errors and misconfigurations. Pay close attention to all commands and do not ignore any one of them.  

### Prerequisites

First, we have to create a proper environment where our build tasks will be executed. As we are here using the Windows Operating System we have to setup a Unix-like environment for using our compiler toolchain and scripts. Two of the most important tools in the next steps will be the MSYS console and the MinGW compiler toolchain.

**MSYS Setup** 

Download it from [here](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download). 

Start the Setup executable and select *All Packages/MSYS* in the installation manager. In the newly opened window select the following packages:

* *msys-base-bin*
* *msys-autoconf-bin*
* *msys-automake-bin*
* *msys-libtool-bin*

After having selected them click the menu *Installation/Apply changes*
I've installed my MSYS under `C:/bin/mingwX` (I have several versions of it and didn't want to mess them up).

**MinGW Setup** 

Download it from [here](http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/4.9.2/threads-posix/dwarf/i686-4.9.2-release-posix-dwarf-rt_v3-rev1.7z/download).

Unpack the contents of this package somewhere on your disk. I have it under *C:\bin\toolchains\mingw32*

Then expand you system PATH variable so that it contains the location of the *bin* directory from the above MinGW.

`PATH=C:\bin\toolchains\mingw32\bin;YOUR_OTHER_VARIABLES`

The usual way to change those settings is via System/Environment Variables

![env-vars](https://img3.picload.org/image/ddilaorl/env_vars.png)

Click `Environment Variables`, then search for the entry `PATH` in the newly opened window. Click on `New` and add the **full path** to the *bin* subdirectory of mingw. Take care of moving the entry to the top of the list. Just in case you have several GCC compilers available.

![env-settings](https://img2.picload.org/image/ddiloirw/env_settings.png)


Apply those changes, close the toolboxes and open a DOS window. Type `gcc -v` to check if you get a response like this one:

```
$ gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=c:/bin/toolchains/mingw32/bin/../libexec/gcc/i686-w64-mingw32/4.9.2/lto-wrapper.exe
Target: i686-w64-mingw32
Configured with: ../../../src/gcc-4.9.2/configure --host=i686-w64-mingw32 --build=i686-w64-mingw32 --target=i686-w64-mingw32 --prefix=/mingw32 --with-sysroot=/c/mingw492/i686-492-posix-dwarf-rt_v3-rev1/mingw32 --with-gxx-include-dir=/mingw32/i686-w64-mingw32/include/c++ --enable-shared --enable-static --disable-multilib --enable-languages=ada,c,c++,fortran,objc,obj-c++,lto --enable-libstdcxx-time=yes --enable-threads=posix --enable-libgomp --enable-libatomic --enable-lto --enable-graphite --enable-checking=release --enable-fully-dynamic-string --enable-version-specific-runtime-libs --disable-sjlj-exceptions --with-dwarf2 --disable-isl-version-check --disable-cloog-version-check --disable-libstdcxx-pch --disable-libstdcxx-debug --enable-bootstrap --disable-rpath --disable-win32-registry --disable-nls --disable-werror --disable-symvers --with-gnu-as --with-gnu-ld --with-arch=i686 --with-tune=generic --with-libiconv --with-system-zlib --with-gmp=/c/mingw492/prerequisites/i686-w64-mingw32-static --with-mpfr=/c/mingw492/prerequisites/i686-w64-mingw32-static --with-mpc=/c/mingw492/prerequisites/i686-w64-mingw32-static --with-isl=/c/mingw492/prerequisites/i686-w64-mingw32-static --with-cloog=/c/mingw492/prerequisites/i686-w64-mingw32-static --enable-cloog-backend=isl --with-pkgversion='i686-posix-dwarf-rev1, Built by MinGW-W64 project' --with-bugurl=http://sourceforge.net/projects/mingw-w64 CFLAGS='-O2 -pipe -I/c/mingw492/i686-492-posix-dwarf-rt_v3-rev1/mingw32/opt/include -I/c/mingw492/prerequisites/i686-zlib-static/include -I/c/mingw492/prerequisites/i686-w64-mingw32-static/include' CXXFLAGS='-O2 -pipe -I/c/mingw492/i686-492-posix-dwarf-rt_v3-rev1/mingw32/opt/include -I/c/mingw492/prerequisites/i686-zlib-static/include -I/c/mingw492/prerequisites/i686-w64-mingw32-static/include' CPPFLAGS= LDFLAGS='-pipe -L/c/mingw492/i686-492-posix-dwarf-rt_v3-rev1/mingw32/opt/lib -L/c/mingw492/prerequisites/i686-zlib-static/lib -L/c/mingw492/prerequisites/i686-w64-mingw32-static/lib -Wl,--large-address-aware'
Thread model: posix
gcc version 4.9.2 (i686-posix-dwarf-rev1, Built by MinGW-W64 project)
```

If you see this then you've successfully configured your GCC compiler! :thumbsup:



### Installing Libraries

After having installed the MSYS & MinGW tools the next steps will be to download and compile certain libraries which we'll need to compile the DeepOnion Wallet. As some of those libraries come from the Unix world it is **absolutely necessary** to use **unix tools** to unpack them. In our case we'll use `tar`, so it's recommended to [learn a bit about this tool](https://kb.iu.edu/d/acfi). But this isn't a strict requirement, as one only has to type certain commands into the console. 

Here I'll use `C:\deps` as the root directory for the below libraries. If not stated otherwise, all of them will be unpacked there.

![all-libs](https://img3.picload.org/image/ddilowgw/all_libs.png)

#### OpenSSL

Download OpenSSL [from here](http://www.openssl.org/source/openssl-1.0.1l.tar.gz) and unpack it with `tar xvfz openssl-1.0.1l.tar.gz`

Then `cd openssl-1.0.1l` and execute the configuration tool with:

`./Configure no-zlib no-shared no-dso no-krb5 no-camellia no-capieng no-cast no-cms no-dtls1 no-gost no-gmp no-heartbeats no-idea no-jpake no-md2 no-mdc2 no-rc5 no-rdrand no-rfc3779 no-rsax no-sctp no-seed no-sha0 no-static_engine no-whirlpool no-rc2 no-rc4 no-ssl2 no-ssl3 mingw`

Wait for it to complete and then build the library with `make`

After the completion has finished you'll get some new files inside the **openssl** directory: `libssl.a` and `libcrypto.a`

Those libraries, and many others from the upcoming steps, will later be used by the QT build scripts to create the Wallet. Now the following steps will be described in a *less verbose* manner.

#### Berkeley DB

[Download](http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz)

```
tar xvfz db-4.8.30.NC.tar.gz
cd db-4.8.30.NC/build_unix
../dist/configure --enable-mingw --enable-cxx --disable-shared --disable-replication
make
```

#### Boost 1.57

[Download](http://sourceforge.net/projects/boost/files/boost/1.57.0/)

This library is *OS agnostic* and should therefore be unpacked by 7zip which you can download from [here](http://www.7-zip.org/). **Do not try to unpack it with** *tar* **like you did with previous libraries!**

```
bootstrap.bat mingw
b2 --build-type=complete --with-chrono --with-filesystem --with-program_options --with-system --with-thread toolset=gcc variant=release link=static threading=multi runtime-link=static stage

```

The compiled libraries will land in the `stage/lib` directory as stated in the command above.

![boost-stage](https://img2.picload.org/image/ddilaioi/boost_stage.png)

#### MiniUPNPC

[Download](http://miniupnp.free.fr/files/download.php?file=miniupnpc-1.9.20150206.tar.gz)

After unpacking with *tar* rename the folder to *miniupnpc* first before building it.

```
tar xvfz miniupnpc-1.9.20150206.tar.gz
cd miniupnpc
mingw32-make -f Makefile.mingw init upnpc-static
```

#### PROTOC & PROTOBUF

[Download](https://github.com/google/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.gz)

```
tar xvfz protobuf-2.6.1.tar.gz
cd protobuf-2.6.1
configure --disable-shared
make
```

#### LibPNG & QREncode

[Download](http://download.sourceforge.net/libpng/libpng-1.6.34.tar.gz) LibPNG

```
tar xvfz libpng-1.6.34.tar.gz
cd libpng-1.6.34
configure --disable-shared
make
cp .libs/libpng16.a .libs/libpng.a
```

Then [download](http://fukuchi.org/works/qrencode/qrencode-3.4.4.tar.gz) QrEncode.

```
cd qrencode-3.4.4

LIBS="../libpng-1.6.34/.libs/libpng.a C:/bin/toolchains/mingw32/i686-w64-mingw32/lib/libz.a" \
png_CFLAGS="-I../libpng-1.6.34" \
png_LIBS="-L../libpng-1.6.34/.libs" \
configure --enable-static --disable-shared --without-tools

make
```

As you can see in the above snippet, there are some paths needed for  proper compilation. Take care of providing your own paths if you're not using *C:/bin/toolchains/mingw32* as the root directory for your MinGW compiler. 

Regarding LibPNG in the **LIBS** variable: *make sure you're pointing to the correct path!* 

In this case I've used relative ones, but you're free to hard code them according to your local structure. If you encounter any errors during compilation of *QrEncode*, look at those paths first, as this is the most frequent source of problems.

#### Libcommuni

[Download](https://github.com/communi/libcommuni/archive/v3.5.0.zip)
Unzip the package with 7zip.

```
qmake
make
```

Regarding potential issues with **Qmake tool** scroll down to the QT section and look under the *Potential Issues* paragraph. 

#### LibEvent

[Download](https://sourceforge.net/projects/levent/files/release-2.0.22-stable/libevent-2.0.22-stable.tar.gz/download).

After unpacking rename the directory to libevent-2.0.22.

```
tar xvfz libevent-2.0.22-stable.tar.gz
cd libevent-2.0.22
./configure --prefix=/mingw
./configure && make
make install
```

#### TOR Libraries

The DeepOnion project delivers pre-compiled TOR libraries so there is no need to compile them again. However, in case of a new version or for testing purposes one can easily compile them by executing the following commands in a MSYS window:

```
cd TOR_UNPACKED_SRC_DIRECTORY
./configure --enable-static-tor --enable-static-libevent --with-libevent-dir=c:/deps/libevent-2.0.22 --with-openssl-dir=c:/deps/openssl-1.0.1l --wi
th-zlib-dir=C:/bin/toolchains/mingw32/i686-w64-mingw32/lib --disable-asciidoc
make
```

Here, again, take care of providing **your own paths to compiler toolchains**. After the compilation has finished copy those libraries to our default `src/torlibs-win` path. You can see the list of all libraries inside the Qt Project file.

![tor-libs-paths](https://img3.picload.org/image/ddillpla/tor_libs_paths.png)



#### QT Libraries

You have to download two packages from QT: [QtBase](https://download.qt.io/archive/qt/5.3/5.3.2/submodules/qtbase-opensource-src-5.3.2.7z) & [QtTools](https://download.qt.io/archive/qt/5.3/5.3.2/submodules/qttools-opensource-src-5.3.2.7z). **Those libraries must be unpacked with 7zip!**

My local root for is `C:/Qt/5.3.2` for **QtBase** and `C:/Qt/qt-tools-opensource-src-5.3.2` for **QtTools**.

![qt-root](https://img2.picload.org/image/ddilorgr/qt_root.png)

Open a Windows command prompt (not MSYS!) and type the following commands one by one.

```
set INCLUDE=C:\deps\libpng-1.6.34;C:\deps\openssl-1.0.1l\include

set LIB=C:\deps\libpng-1.6.34\.libs;C:\deps\openssl-1.0.1l

cd C:\Qt\5.3.2

configure.bat -release -opensource -confirm-license -static -make libs -no-sql-sqlite -no-opengl -system-zlib -qt-pcre -no-icu -no-gif -system-libpng -no-libjpeg -no-freetype -no-angle -no-vcproj -openssl -no-dbus -no-audio-backend -no-wmf-backend -no-qml-debug

mingw32-make

set PATH=%PATH%;C:\Qt\5.3.2\bin

cd C:\Qt\qttools-opensource-src-5.3.2

qmake qttools.pro

mingw32-make
```

#### Potential Issues

**Problem:** *Using wrong QMake*

One aspect is the location of the *qmake* tool which in my case was located in two places. One was the Qt directory itself (which should have been used) and the other was a package brought by my Anaconda Toolset which I'm using when coding in Python. This, of course, had nothing to do with DeepOnion or C++ development at all, but it happened that in my case Anaconda's location got evaluated first and the end result was a messy Makefile. So, if you experience similar things the first command you should enter is `which qmake` to list all available locations of it. In my case the result was this one:

`c:\bin\Anaconda3\Library\bin\qmake`

Therefore I had to use the full path to the 'correct' Qmake:

`C:\Qt\5.3.2\bin\qmake.exe`

**Problem:** *Windows-style Paths*

Another problem is the correct writing of paths inside the generated Makefiles (Debug & Release versions). I have run into problems with the location of `C:/Qt/5.3.2/bin/uic.exe` which was originally written as `C:\Qt\5.3.2\bin\uic.exe`. You'll have to replace all of them inside the Makefile. Qt seems to have problems with Windows-styled paths.

But before you can generate a proper Makefile you'll have to adjust your local paths inside the DeepOnion.pro (the QT project file) as well. Open this file in your editor and go to the line 23. You'll see several paths that look like this:

![qt-pro-original](https://img3.picload.org/image/ddilolcl/qt_pro_original.png)

You'll have to set the paths to your locally compiled libraries. Here's how my local [DeepOnion.pro](https://github.com/brakmic/deeponion/blob/qt-local/DeepOnion-qt.pro) looks like:

![qt-pro-local](https://img1.picload.org/image/ddilocol/qt-local.png) 

#### Compiling LevelDb

You'll also have to manually kickoff the compilation of *leveldb* by executing the following command in a MSYS window:

```
cd src/leveldb
TARGET_OS=OS_WINDOWS_CROSSCOMPILE make libleveldb.a libmemenv.a
```

#### Compiling DeepOnion

Now, it's time to type in a MSYS window the following commands:

```
qmake
make
```

If the compilation succeeds you'll get the executables inside the *src* directory.

Have fun with [DeepOnion](https://deeponion.org/)! :heart: