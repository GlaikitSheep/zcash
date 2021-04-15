#include <gtest/gtest.h>

#include "gtest/utils.h"
#include "primitives/transaction.h"
#include "transaction_builder.h"
#include "votecoin/Note.hpp"
#include "votecoin/Address.hpp"

#include <array>

#include <rust/ed25519/types.h>

TEST(Transaction, JSDescriptionRandomized) {
    // construct a merkle tree
    SproutMerkleTree merkleTree;

    libvotecoin::SproutSpendingKey k = libvotecoin::SproutSpendingKey::random();
    libvotecoin::SproutPaymentAddress addr = k.address();

    libvotecoin::SproutNote note(addr.a_pk, 100, uint256(), uint256());

    // commitment from coin
    uint256 commitment = note.cm();

    // insert commitment into the merkle tree
    merkleTree.append(commitment);

    // compute the merkle root we will be working with
    uint256 rt = merkleTree.root();

    auto witness = merkleTree.witness();

    // create JSDescription
    Ed25519VerificationKey joinSplitPubKey;
    std::array<libvotecoin::JSInput, ZC_NUM_JS_INPUTS> inputs = {
        libvotecoin::JSInput(witness, note, k),
        libvotecoin::JSInput() // dummy input of zero value
    };
    std::array<libvotecoin::JSOutput, ZC_NUM_JS_OUTPUTS> outputs = {
        libvotecoin::JSOutput(addr, 50),
        libvotecoin::JSOutput(addr, 50)
    };
    std::array<size_t, ZC_NUM_JS_INPUTS> inputMap;
    std::array<size_t, ZC_NUM_JS_OUTPUTS> outputMap;

    {
        auto jsdesc = JSDescriptionInfo(
            joinSplitPubKey, rt,
            inputs, outputs,
            0, 0
        ).BuildRandomized(
            inputMap, outputMap,
            false);

        std::set<size_t> inputSet(inputMap.begin(), inputMap.end());
        std::set<size_t> expectedInputSet {0, 1};
        EXPECT_EQ(expectedInputSet, inputSet);

        std::set<size_t> outputSet(outputMap.begin(), outputMap.end());
        std::set<size_t> expectedOutputSet {0, 1};
        EXPECT_EQ(expectedOutputSet, outputSet);
    }

    {
        auto jsdesc = JSDescriptionInfo(
            joinSplitPubKey, rt,
            inputs, outputs,
            0, 0
        ).BuildRandomized(
            inputMap, outputMap,
            false, nullptr, GenZero);

        std::array<size_t, ZC_NUM_JS_INPUTS> expectedInputMap {1, 0};
        std::array<size_t, ZC_NUM_JS_OUTPUTS> expectedOutputMap {1, 0};
        EXPECT_EQ(expectedInputMap, inputMap);
        EXPECT_EQ(expectedOutputMap, outputMap);
    }

    {
        auto jsdesc = JSDescriptionInfo(
            joinSplitPubKey, rt,
            inputs, outputs,
            0, 0
        ).BuildRandomized(
            inputMap, outputMap,
            false, nullptr, GenMax);

        std::array<size_t, ZC_NUM_JS_INPUTS> expectedInputMap {0, 1};
        std::array<size_t, ZC_NUM_JS_OUTPUTS> expectedOutputMap {0, 1};
        EXPECT_EQ(expectedInputMap, inputMap);
        EXPECT_EQ(expectedOutputMap, outputMap);
    }
}
