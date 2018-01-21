AM_CPPFLAGS =  $(INCLUDES) 
AM_LDFLAGS = $(PTHREAD_CFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS)"
endif

BITCOIN_CONFIG_INCLUDES=-I$(builddir)/config
BITCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS)

LIBBITCOIN_SERVER=libbitcoin_server.a
LIBBITCOIN_WALLET=libbitcoin_wallet.a
LIBBITCOIN_COMMON=libbitcoin_common.a

LIBBITCOIN_UTIL=libbitcoin_util.a
if HAVE_SSE2
IBBITCOIN_SSE2=libbitcoin_sse2.a
endif

LIBBITCOINQT=qt/libbitcoinqt.a

noinst_LIBRARIES = \
  libbitcoin_server.a \
  libbitcoin_common.a \
  libbitcoin_util.a
if ENABLE_WALLET
BITCOIN_INCLUDES += $(BDB_CPPFLAGS)
noinst_LIBRARIES += libbitcoin_wallet.a
endif

if HAVE_SSE2
noinst_LIBRARIES += libbitcoin_sse2.a
endif

bin_PROGRAMS =
TESTS =

if BUILD_BITCOIND
  bin_PROGRAMS += DeepOniond
endif

.PHONY: FORCE
# bitcoin core #
BITCOIN_CORE_H = \
  anonymize.h \
  addrman.h \
  alert.h \
  allocators.h \
  base58.h \
  bignum.h \
  bloom.h \
  checkpoints.h \
  checkqueue.h \
  coincontrol.h \
  compat.h \
  crypter.h \
  db.h \
  hash.h \
  hashblock.h \
  init.h \
  key.h \
  keystore.h \
  limitedmap.h \
  main.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  protocol.h \
  rpcclient.h \
  script.h \
  serialize.h \
  smessage.h \
  sync.h \
  threadsafety.h \
  tinyformat.h \
  txdb-leveldb.h \
  ui_interface.h \
  uint256.h \
  util.h \
  scrypt.h \
  strlcpy.h \
  version.h \
  walletdb.h \
  wallet.h \
  sph_blake.h \
  sph_bmw.h \
  sph_cubehash.h \
  sph_echo.h \
  sph_fugue.h \
  sph_groestl.h \
  sph_hamsi.h \
  sph_jh.h \
  sph_keccak.h \
  sph_luffa.h \
  sph_shavite.h \
  sph_simd.h \
  sph_skein.h \
  sph_types.h \
  pbkdf2.h 

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libbitcoin_util_a-version.$(OBJEXT): obj/build.h

# server: shared between bitcoind and bitcoin-qt
libbitcoin_server_a_CPPFLAGS = $(BITCOIN_INCLUDES)
libbitcoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  checkpoints.cpp \
  init.cpp \
  db.cpp \
  txdb-leveldb.cpp \
  bitcoinrpc.cpp \
  keystore.cpp \
  main.cpp \
  noui.cpp \
  net.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcsmessage.cpp \
  $(JSON_H) \
  $(BITCOIN_CORE_H)

# wallet: shared between bitcoind and bitcoin-qt, but only linked
# when wallet enabled
libbitcoin_wallet_a_CPPFLAGS = $(BITCOIN_INCLUDES)
libbitcoin_wallet_a_SOURCES = \
  crypter.cpp \
  scrypt.cpp \
  scrypt-sse2.cpp \
  pbkdf2.cpp \
  rpcdump.cpp \
  rpcwallet.cpp \
  rpcsmessage.cpp \
  wallet.cpp \
  walletdb.cpp \
  $(BITCOIN_CORE_H)

# common: shared between bitcoind, and bitcoin-qt and non-server tools
libbitcoin_common_a_CPPFLAGS = $(BITCOIN_INCLUDES)
libbitcoin_common_a_SOURCES = \
  anonymize.cpp \
  hash.cpp \
  key.cpp \
  netbase.cpp \
  protocol.cpp \
  smessage.cpp \
  script.cpp \
  kernel.cpp \
  miner.cpp \
  sync.cpp \
  util.cpp \
  version.cpp \
  aes_helper.c \
  blake.c \
  bmw.c \
  cubehash.c \
  fugue.c \
  echo.c \
  groestl.c \
  hamsi_helper.c \
  hamsi.c \
  jh.c \
  keccak.c \
  luffa.c \
  shavite.c \
  simd.c \
  skein.c \
  $(BITCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libbitcoin_util_a_CPPFLAGS = $(BITCOIN_INCLUDES)
libbitcoin_util_a_SOURCES = \
  sync.cpp \
  util.cpp \
  $(BITCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libbitcoin_util_a_SOURCES += compat/glibc_compat.cpp
libbitcoin_util_a_SOURCES += compat/glibcxx_compat.cpp
endif

nodist_libbitcoin_util_a_SOURCES = $(srcdir)/obj/build.h
# bitcoind binary #
DeepOniond_LDADD = \
  $(LIBBITCOIN_SERVER) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBLEVELDB) \
  $(LIBMEMENV)

if HAVE_SSE2
libbitcoin_sse2_a_SOURCES = scrypt-sse2.cpp
libbitcoin_sse2_a_CPPFLAGS = $(BITCOIN_INCLUDES) -msse2 -mstackrealign
DeepOniond_LDADD += libbitcoin_sse2.a
endif

if ENABLE_WALLET
DeepOniond_LDADD += libbitcoin_wallet.a
endif
DeepOniond_SOURCES = daemon.cpp

DeepOniond_LDADD += \
  ../tor/src/or/libtor.a \
  ../tor/src/common/libor.a \
  ../tor/src/common/libor-ctime.a \
  ../tor/src/common/libor-crypto.a \
  ../tor/src/common/libor-event.a \
  ../tor/src/trunnel/libor-trunnel.a \
  ../tor/src/common/libcurve25519_donna.a \
  ../tor/src/ext/ed25519/donna/libed25519_donna.a \
  ../tor/src/ext/ed25519/ref10/libed25519_ref10.a \
  ../tor/src/ext/keccak-tiny/libkeccak-tiny.a \
  $(LIBEVENT_LIBS) \
  $(LIBSECCOMP_LIBS) \
  $(LIBCAP_LIBS) \
  $(ZLIB_LIBS)

DeepOniond_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(LIBEVENT_LDFLAGS) $(LIBSECCOMP_LDFLAGS) $(LIBCAP_LDFLAGS) $(ZLIB_LDFLAGS)
DeepOniond_CPPFLAGS = $(BITCOIN_INCLUDES) $(LIBEVENT_CFLAGS) $(LIBSECCOMP_CFLAGS) $(LIBCAP_CFLAGS) $(ZLIB_CFLAGS)

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_QT
include Makefile.qt.include
endif
