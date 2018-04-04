#!/bin/bash -e

[ -d .git ] && [ -d tor ] && [ -d src/leveldb ] || \
  { echo "Please run this command from the root of a recursive Git clone of the DeepOnion repository." && exit 1; }

git submodule init 
git submodule sync --recursive 
git submodule update --recursive --force

autoreconf --no-recursive --install

PATCH="patch --no-backup-if-mismatch -f"

pushd tor
#$PATCH -p0 < ../tor-or-am.patch
#$PATCH -p0 < ../tor-am.patch
./autogen.sh
popd
pushd src/leveldb
$PATCH -p0 < ../../leveldb.patch
popd
