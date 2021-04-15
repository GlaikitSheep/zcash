// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2016-2018 The VoteCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php .

#ifndef BITCOIN_KEY_IO_H
#define BITCOIN_KEY_IO_H

#include <chainparams.h>
#include <key.h>
#include <pubkey.h>
#include <script/standard.h>
#include <votecoin/Address.hpp>

#include <vector>
#include <string>

class KeyIO {
private:
    const KeyConstants& keyConstants;

public:
    KeyIO(const KeyConstants& keyConstants): keyConstants(keyConstants) { }

    CKey DecodeSecret(const std::string& str);
    std::string EncodeSecret(const CKey& key);

    CExtKey DecodeExtKey(const std::string& str);
    std::string EncodeExtKey(const CExtKey& extkey);
    CExtPubKey DecodeExtPubKey(const std::string& str);
    std::string EncodeExtPubKey(const CExtPubKey& extpubkey);

    std::string EncodeDestination(const CTxDestination& dest);
    CTxDestination DecodeDestination(const std::string& str);

    bool IsValidDestinationString(const std::string& str);

    std::string EncodePaymentAddress(const libvotecoin::PaymentAddress& zaddr);
    libvotecoin::PaymentAddress DecodePaymentAddress(const std::string& str);
    bool IsValidPaymentAddressString(const std::string& str);

    std::string EncodeViewingKey(const libvotecoin::ViewingKey& vk);
    libvotecoin::ViewingKey DecodeViewingKey(const std::string& str);

    std::string EncodeSpendingKey(const libvotecoin::SpendingKey& zkey);
    libvotecoin::SpendingKey DecodeSpendingKey(const std::string& str);
};

#endif // BITCOIN_KEY_IO_H
