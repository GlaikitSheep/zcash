# Copyright (c) 2016-2019 The VoteCoin developers
# Copyright (c) 2013-2019 The Bitcoin Core developers
# Copyright (c) 2013-2019 Bitcoin Developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://www.opensource.org/licenses/mit-license.php .

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

BITCOIN_CONFIG_INCLUDES=-I$(builddir)/config
BITCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS)

BITCOIN_CONFIG_INCLUDES += -I$(srcdir)/rust/include
BITCOIN_INCLUDES += -I$(srcdir)/rust/include
BITCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
BITCOIN_INCLUDES += -I$(srcdir)/univalue/include

LIBBITCOIN_SERVER=libbitcoin_server.a
LIBBITCOIN_COMMON=libbitcoin_common.a
LIBBITCOIN_CLI=libbitcoin_cli.a
LIBBITCOIN_UTIL=libbitcoin_util.a
LIBBITCOIN_CRYPTO=crypto/libbitcoin_crypto.a
LIBRUSTZCASH=$(top_builddir)/target/$(RUST_TARGET)/release/librustzcash.a
LIBSECP256K1=secp256k1/libsecp256k1.la
LIBUNIVALUE=univalue/libunivalue.la
LIBVOTECOIN=libvotecoin.a

if ENABLE_ZMQ
LIBBITCOIN_ZMQ=libbitcoin_zmq.a
endif
if BUILD_BITCOIN_LIBS
LIBVOTECOIN_SCRIPT=libvotecoin_script.la
endif
if ENABLE_WALLET
LIBBITCOIN_WALLET=libbitcoin_wallet.a
endif

RUST_ENV_VARS = RUSTC="$(RUSTC)" TERM=dumb
RUST_BUILD_OPTS = --lib --release --target $(RUST_TARGET)

rust_verbose = $(rust_verbose_@AM_V@)
rust_verbose_ = $(rust_verbose_@AM_DEFAULT_V@)
rust_verbose_1 = --verbose

if ENABLE_ONLINE_RUST
# Ensure that .cargo/config does not exist
CARGO_CONFIGURED = $(top_srcdir)/.cargo/.configured-for-online
$(CARGO_CONFIGURED):
	$(AM_V_at)rm -f $(top_srcdir)/.cargo/.configured-for-offline $(top_srcdir)/.cargo/config
	$(AM_V_at)touch $@

else
# Enable dependency vendoring
RUST_BUILD_OPTS += --locked --offline

CARGO_CONFIGURED = $(top_srcdir)/.cargo/.configured-for-offline
$(CARGO_CONFIGURED): $(top_srcdir)/.cargo/config.offline
	$(AM_V_at)rm -f $(top_srcdir)/.cargo/.configured-for-online
	$(AM_V_at)cp $< $(top_srcdir)/.cargo/config
	$(AM_V_at)echo "directory = \"$(RUST_VENDORED_SOURCES)\"" >>$(top_srcdir)/.cargo/config
	$(AM_V_at)touch $@
endif

cargo-build: $(CARGO_CONFIGURED)
	$(RUST_ENV_VARS) $(CARGO) build $(RUST_BUILD_OPTS) $(rust_verbose) --manifest-path $(top_srcdir)/Cargo.toml

$(LIBRUSTZCASH): cargo-build

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_SERVER) \
  $(LIBBITCOIN_CLI) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_ZMQ) \
  $(LIBVOTECOIN)

lib_LTLIBRARIES = $(LIBVOTECOIN_SCRIPT)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_BITCOIND
  bin_PROGRAMS += votecoind
endif

if BUILD_BITCOIN_UTILS
  bin_PROGRAMS += votecoin-cli votecoin-tx
endif

LIBVOTECOIN_H = \
  votecoin/IncrementalMerkleTree.hpp \
  votecoin/NoteEncryption.hpp \
  votecoin/Address.hpp \
  votecoin/address/sapling.hpp \
  votecoin/address/sprout.hpp \
  votecoin/address/zip32.h \
  votecoin/History.hpp \
  votecoin/JoinSplit.hpp \
  votecoin/Note.hpp \
  votecoin/prf.h \
  votecoin/Proof.hpp \
  votecoin/util.h \
  votecoin/VoteCoin.h

.PHONY: FORCE cargo-build check-symbols check-security
# bitcoin core #
BITCOIN_CORE_H = \
  addrdb.h \
  addressindex.h \
  addrman.h \
  alert.h \
  amount.h \
  arith_uint256.h \
  asyncrpcoperation.h \
  asyncrpcqueue.h \
  base58.h \
  bech32.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/funding.h \
  consensus/params.h \
  consensus/upgrades.h \
  consensus/validation.h \
  core_io.h \
  core_memusage.h \
  deprecation.h \
  experimental_features.h \
  fs.h \
  hash.h \
  httprpc.h \
  httpserver.h \
  init.h \
  key.h \
  key_constants.h \
  key_io.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  logging.h \
  main.h \
  memusage.h \
  merkleblock.h \
  metrics.h \
  miner.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  pow.h \
  prevector.h \
  primitives/block.h \
  primitives/transaction.h \
  proof_verifier.h \
  protocol.h \
  pubkey.h \
  random.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/interpreter.h \
  script/script.h \
  script/script_error.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  serialize.h \
  spentindex.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  timestampindex.h \
  tinyformat.h \
  torcontrol.h \
  transaction_builder.h \
  txdb.h \
  mempool_limit.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  uint252.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltest.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  wallet/asyncrpcoperation_common.h \
  wallet/asyncrpcoperation_mergetoaddress.h \
  wallet/asyncrpcoperation_saplingmigration.h \
  wallet/asyncrpcoperation_sendmany.h \
  wallet/asyncrpcoperation_shieldcoinbase.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/paymentdisclosure.h \
  wallet/paymentdisclosuredb.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libbitcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: votecoind
libbitcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libbitcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_server_a_SOURCES = \
  sendalert.cpp \
  addrman.cpp \
  addrdb.cpp \
  alert.cpp \
  alertkeys.h \
  asyncrpcoperation.cpp \
  asyncrpcqueue.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  deprecation.cpp \
  experimental_features.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  metrics.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  mempool_limit.cpp \
  txmempool.cpp \
  validationinterface.cpp \
  $(BITCOIN_CORE_H) \
  $(LIBVOTECOIN_H)

if ENABLE_ZMQ
libbitcoin_zmq_a_CPPFLAGS = $(BITCOIN_INCLUDES) $(ZMQ_CFLAGS)
libbitcoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif

# wallet: votecoind, but only linked when wallet enabled
libbitcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_wallet_a_SOURCES = \
  zcbenchmarks.cpp \
  zcbenchmarks.h \
  wallet/asyncrpcoperation_common.cpp \
  wallet/asyncrpcoperation_mergetoaddress.cpp \
  wallet/asyncrpcoperation_saplingmigration.cpp \
  wallet/asyncrpcoperation_sendmany.cpp \
  wallet/asyncrpcoperation_shieldcoinbase.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/paymentdisclosure.cpp \
  wallet/paymentdisclosuredb.cpp \
  wallet/rpcdisclosure.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  $(BITCOIN_CORE_H) \
  $(LIBVOTECOIN_H)

# crypto primitives library
crypto_libbitcoin_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_CONFIG_INCLUDES)
crypto_libbitcoin_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libbitcoin_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/equihash.cpp \
  crypto/equihash.h \
  crypto/equihash.tcc \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

if ENABLE_MINING
EQUIHASH_TROMP_SOURCES = \
  pow/tromp/equi_miner.h \
  pow/tromp/equi.h \
  pow/tromp/osx_barrier.h

crypto_libbitcoin_crypto_a_CPPFLAGS += \
  -DEQUIHASH_TROMP_ATOMIC
crypto_libbitcoin_crypto_a_SOURCES += \
  ${EQUIHASH_TROMP_SOURCES}
endif

# common: shared between votecoind and non-server tools
libbitcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_common_a_SOURCES = \
  amount.cpp \
  arith_uint256.cpp \
  base58.cpp \
  bech32.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  consensus/funding.cpp \
  consensus/params.cpp \
  consensus/upgrades.cpp \
  core_read.cpp \
  core_write.cpp \
  hash.cpp \
  key.cpp \
  key_io.cpp \
  keystore.cpp \
  netbase.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  proof_verifier.cpp \
  protocol.cpp \
  pubkey.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sign.cpp \
  script/standard.cpp \
  transaction_builder.cpp \
  utiltest.cpp \
  warnings.cpp \
  $(BITCOIN_CORE_H) \
  $(LIBVOTECOIN_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libbitcoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  logging.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(BITCOIN_CORE_H) \
  $(LIBVOTECOIN_H)

if GLIBC_BACK_COMPAT
libbitcoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: votecoin-cli
libbitcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libbitcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libbitcoin_cli_a_SOURCES = \
  rpc/client.cpp \
  $(BITCOIN_CORE_H) \
  $(LIBVOTECOIN_H)

nodist_libbitcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# bitcoind binary #
votecoind_SOURCES = bitcoind.cpp
votecoind_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
votecoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
votecoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
votecoind_SOURCES += bitcoind-res.rc
endif

votecoind_LDADD = \
  $(LIBBITCOIN_SERVER) \
  $(LIBBITCOIN_WALLET) \
  $(LIBBITCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_UTIL) \
  $(LIBBITCOIN_ZMQ) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBVOTECOIN) \
  $(LIBRUSTZCASH) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

votecoind_LDADD += \
  $(BOOST_LIBS) \
  $(BDB_LIBS) \
  $(EVENT_PTHREADS_LIBS) \
  $(EVENT_LIBS) \
  $(ZMQ_LIBS) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBVOTECOIN_LIBS)

# bitcoin-cli binary #
votecoin_cli_SOURCES = bitcoin-cli.cpp
votecoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(EVENT_CFLAGS)
votecoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
votecoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
votecoin_cli_SOURCES += bitcoin-cli-res.rc
endif

votecoin_cli_LDADD = \
  $(LIBBITCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_UTIL) \
  $(BOOST_LIBS) \
  $(EVENT_LIBS) \
  $(LIBVOTECOIN) \
  $(LIBRUSTZCASH) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBVOTECOIN_LIBS)
#

# votecoin-tx binary #
votecoin_tx_SOURCES = bitcoin-tx.cpp
votecoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
votecoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
votecoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
votecoin_tx_SOURCES += bitcoin-tx-res.rc
endif

# FIXME: Is libvotecoin needed for votecoin_tx?
votecoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBBITCOIN_COMMON) \
  $(LIBBITCOIN_UTIL) \
  $(LIBSECP256K1) \
  $(LIBVOTECOIN) \
  $(LIBRUSTZCASH) \
  $(LIBBITCOIN_CRYPTO) \
  $(LIBVOTECOIN_LIBS)

votecoin_tx_LDADD += $(BOOST_LIBS)
#

# votecoin protocol primitives #
libvotecoin_a_SOURCES = \
  votecoin/IncrementalMerkleTree.cpp \
  votecoin/NoteEncryption.cpp \
  votecoin/Address.cpp \
  votecoin/address/sapling.cpp \
  votecoin/address/sprout.cpp \
  votecoin/address/zip32.cpp \
  votecoin/History.cpp \
  votecoin/JoinSplit.cpp \
  votecoin/Note.cpp \
  votecoin/prf.cpp \
  votecoin/util.cpp

libvotecoin_a_CPPFLAGS = $(AM_CPPFLAGS) $(PIC_FLAGS) $(BITCOIN_INCLUDES)
libvotecoin_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libvotecoin_a_LDFLAGS = $(AM_LDFLAGS)

# votecoin_script library #
if BUILD_BITCOIN_LIBS
include_HEADERS = script/votecoin_script.h
libvotecoin_script_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/votecoin_script.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libvotecoin_script_la_SOURCES += compat/glibc_compat.cpp
endif

libvotecoin_script_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libvotecoin_script_la_LIBADD = $(LIBSECP256K1)
libvotecoin_script_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/rust/include -I$(srcdir)/secp256k1/include -DBUILD_BITCOIN_INTERNAL
libvotecoin_script_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = *.gcda *.gcno */*.gcno wallet/*/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = $(CTAES_DIST) rust

clean-local:
	rm -f $(top_srcdir)/.cargo/config $(top_srcdir)/.cargo/.configured-for-*
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	rm -f fuzz.cpp
	rm -rf fuzzing/*/output
	-rm -f config.h
	-rm -f *.lib bench/*.lib test/*.lib

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat of [$(bin_PROGRAMS)]..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security of [$(bin_PROGRAMS)]..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
include Makefile.gtest.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif
