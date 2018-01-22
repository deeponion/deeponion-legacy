#!/bin/bash -e

[ -d .git ] && [ -f ./tor/.git ] || \
  { echo "Please run this command from the root of a recursive Git clone of the DeepOnion repository." && exit 1; }

git submodule init 
git submodule sync --recursive 
git submodule update --recursive --force

pushd tor && git clean -fdx . && popd

autoreconf --no-recursive --install

PATCH="patch --no-backup-if-mismatch -f"

pushd tor
$PATCH -p0 < ../tor-or-am.patch
$PATCH -p0 < ../tor-am.patch
$PATCH -p0 < ../tor-version.patch
./autogen.sh
popd
