// Copyright (c) 2016 The VoteCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php .

#ifndef VOTECOIN_UTILTEST_H
#define VOTECOIN_UTILTEST_H

#include "key_io.h"
#include "wallet/wallet.h"
#include "votecoin/Address.hpp"
#include "votecoin/Note.hpp"
#include "votecoin/NoteEncryption.hpp"

// Sprout
CWalletTx GetValidSproutReceive(const libvotecoin::SproutSpendingKey& sk,
                                CAmount value,
                                bool randomInputs,
                                uint32_t versionGroupId = SAPLING_VERSION_GROUP_ID,
                                int32_t version = SAPLING_TX_VERSION);
CWalletTx GetInvalidCommitmentSproutReceive(
                                const libvotecoin::SproutSpendingKey& sk,
                                CAmount value,
                                bool randomInputs,
                                uint32_t versionGroupId = SAPLING_VERSION_GROUP_ID,
                                int32_t version = SAPLING_TX_VERSION);
libvotecoin::SproutNote GetSproutNote(const libvotecoin::SproutSpendingKey& sk,
                                   const CTransaction& tx, size_t js, size_t n);
CWalletTx GetValidSproutSpend(const libvotecoin::SproutSpendingKey& sk,
                              const libvotecoin::SproutNote& note,
                              CAmount value);

// Sapling
static const std::string T_SECRET_REGTEST = "cND2ZvtabDbJ1gucx9GWH6XT9kgTAqfb6cotPt5Q5CyxVDhid2EN";

struct TestSaplingNote {
    libvotecoin::SaplingNote note;
    SaplingMerkleTree tree;
};

const Consensus::Params& RegtestActivateSapling();

void RegtestDeactivateSapling();

const CChainParams& RegtestActivateBlossom(bool updatePow, int blossomActivationHeight = Consensus::NetworkUpgrade::ALWAYS_ACTIVE);

void RegtestDeactivateBlossom();

const Consensus::Params& RegtestActivateHeartwood(bool updatePow, int heartwoodActivationHeight = Consensus::NetworkUpgrade::ALWAYS_ACTIVE);

void RegtestDeactivateHeartwood();

const Consensus::Params& RegtestActivateCanopy(bool updatePow, int canopyActivationHeight = Consensus::NetworkUpgrade::ALWAYS_ACTIVE);
const Consensus::Params& RegtestActivateCanopy();

void RegtestDeactivateCanopy();

const Consensus::Params& RegtestActivateNU5(bool updatePow, int nu5ActivationHeight = Consensus::NetworkUpgrade::ALWAYS_ACTIVE);
const Consensus::Params& RegtestActivateNU5();

void RegtestDeactivateNU5();

libvotecoin::SaplingExtendedSpendingKey GetTestMasterSaplingSpendingKey();

CKey AddTestCKeyToKeyStore(CBasicKeyStore& keyStore);

/**
 * Generate a dummy SaplingNote and a SaplingMerkleTree with that note's commitment.
 */
TestSaplingNote GetTestSaplingNote(const libvotecoin::SaplingPaymentAddress& pa, CAmount value);

CWalletTx GetValidSaplingReceive(const Consensus::Params& consensusParams,
                                 CBasicKeyStore& keyStore,
                                 const libvotecoin::SaplingExtendedSpendingKey &sk,
                                 CAmount value);

#endif // VOTECOIN_UTILTEST_H
