// Copyright (c) 2020 The VoteCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php .

#ifndef VOTECOIN_EXPERIMENTAL_FEATURES_H
#define VOTECOIN_EXPERIMENTAL_FEATURES_H

#include <optional>
#include <string>
#include <vector>

extern bool fExperimentalDeveloperEncryptWallet;
extern bool fExperimentalDeveloperSetPoolSizeZero;
extern bool fExperimentalPaymentDisclosure;
extern bool fExperimentalInsightExplorer;
extern bool fExperimentalLightWalletd;

std::optional<std::string> InitExperimentalMode();
std::vector<std::string> GetExperimentalFeatures();

#endif // VOTECOIN_EXPERIMENTAL_FEATURES_H
