#!/bin/bash -e

[ -d .git ] && [ -f ./tor/.git ] || \
  { echo "Please run this command from the root of a recursive Git clone of the DeepOnion repository." && exit 1; }

pushd tor && git checkout -f . && git clean -fdx . && popd
git submodule update --init

autoreconf --no-recursive --install

pushd tor
patch --no-backup-if-mismatch -f -p0 < ../tor-or-am.patch
patch --no-backup-if-mismatch -f -p0 < ../tor-am.patch
./autogen.sh
popd
