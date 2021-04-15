// Copyright (c) 2019 The VoteCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php .

#ifndef VOTECOIN_WALLET_ASYNCRPCOPERATION_COMMON_H
#define VOTECOIN_WALLET_ASYNCRPCOPERATION_COMMON_H

#include "primitives/transaction.h"
#include "univalue.h"
#include "wallet.h"

#include <optional>

/**
 * Sends a given transaction.
 * 
 * If testmode is false, commit the transaction to the wallet, 
 * return {"txid": tx.GetHash().ToString()}
 * 
 * If testmode is true, do not commit the transaction,
 * return {"test": 1, "txid": tx.GetHash().ToString(), "hex": EncodeHexTx(tx)}
 */
UniValue SendTransaction(CTransaction& tx, std::optional<std::reference_wrapper<CReserveKey>> reservekey, bool testmode);

/**
 * Sign and send a raw transaction.
 * Raw transaction as hex string should be in object field "rawtxn"
 * 
 * Returns a pair of (the parsed transaction, and the result of sending)
 */
std::pair<CTransaction, UniValue> SignSendRawTransaction(UniValue obj, std::optional<std::reference_wrapper<CReserveKey>> reservekey, bool testmode);

#endif // VOTECOIN_WALLET_ASYNCRPCOPERATION_COMMON_H
