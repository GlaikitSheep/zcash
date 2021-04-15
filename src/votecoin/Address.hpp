#ifndef ZC_ADDRESS_H_
#define ZC_ADDRESS_H_

#include "votecoin/address/sapling.hpp"
#include "votecoin/address/sprout.hpp"
#include "votecoin/address/zip32.h"

#include <variant>

namespace libvotecoin {
class InvalidEncoding {
public:
    friend bool operator==(const InvalidEncoding &a, const InvalidEncoding &b) { return true; }
    friend bool operator<(const InvalidEncoding &a, const InvalidEncoding &b) { return true; }
};

typedef std::variant<InvalidEncoding, SproutPaymentAddress, SaplingPaymentAddress> PaymentAddress;
typedef std::variant<InvalidEncoding, SproutViewingKey, SaplingExtendedFullViewingKey> ViewingKey;
typedef std::variant<InvalidEncoding, SproutSpendingKey, SaplingExtendedSpendingKey> SpendingKey;

class AddressInfoFromSpendingKey {
public:
    std::pair<std::string, PaymentAddress> operator()(const SproutSpendingKey&) const;
    std::pair<std::string, PaymentAddress> operator()(const struct SaplingExtendedSpendingKey&) const;
    std::pair<std::string, PaymentAddress> operator()(const InvalidEncoding&) const;
};

class AddressInfoFromViewingKey {
public:
    std::pair<std::string, PaymentAddress> operator()(const SproutViewingKey&) const;
    std::pair<std::string, PaymentAddress> operator()(const struct SaplingExtendedFullViewingKey&) const;
    std::pair<std::string, PaymentAddress> operator()(const InvalidEncoding&) const;
};

}

/** Check whether a PaymentAddress is not an InvalidEncoding. */
bool IsValidPaymentAddress(const libvotecoin::PaymentAddress& zaddr);

/** Check whether a ViewingKey is not an InvalidEncoding. */
bool IsValidViewingKey(const libvotecoin::ViewingKey& vk);

/** Check whether a SpendingKey is not an InvalidEncoding. */
bool IsValidSpendingKey(const libvotecoin::SpendingKey& zkey);

#endif // ZC_ADDRESS_H_
