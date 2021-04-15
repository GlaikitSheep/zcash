#include "Address.hpp"

namespace libvotecoin {

std::pair<std::string, PaymentAddress> AddressInfoFromSpendingKey::operator()(const SproutSpendingKey &sk) const {
    return std::make_pair("sprout", sk.address());
}
std::pair<std::string, PaymentAddress> AddressInfoFromSpendingKey::operator()(const SaplingExtendedSpendingKey &sk) const {
    return std::make_pair("sapling", sk.DefaultAddress());
}
std::pair<std::string, PaymentAddress> AddressInfoFromSpendingKey::operator()(const InvalidEncoding&) const {
    throw std::invalid_argument("Cannot derive default address from invalid spending key");
}

std::pair<std::string, PaymentAddress> AddressInfoFromViewingKey::operator()(const SproutViewingKey &sk) const {
    return std::make_pair("sprout", sk.address());
}
std::pair<std::string, PaymentAddress> AddressInfoFromViewingKey::operator()(const SaplingExtendedFullViewingKey &sk) const {
    return std::make_pair("sapling", sk.DefaultAddress());
}
std::pair<std::string, PaymentAddress> AddressInfoFromViewingKey::operator()(const InvalidEncoding&) const {
    throw std::invalid_argument("Cannot derive default address from invalid viewing key");
}

}

bool IsValidPaymentAddress(const libvotecoin::PaymentAddress& zaddr) {
    return !std::holds_alternative<libvotecoin::InvalidEncoding>(zaddr);
}

bool IsValidViewingKey(const libvotecoin::ViewingKey& vk) {
    return !std::holds_alternative<libvotecoin::InvalidEncoding>(vk);
}

bool IsValidSpendingKey(const libvotecoin::SpendingKey& zkey) {
    return !std::holds_alternative<libvotecoin::InvalidEncoding>(zkey);
}
