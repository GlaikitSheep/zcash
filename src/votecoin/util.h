#ifndef VOTECOIN_VOTECOIN_UTIL_H
#define VOTECOIN_VOTECOIN_UTIL_H

#include <vector>
#include <cstdint>

std::vector<unsigned char> convertIntToVectorLE(const uint64_t val_int);
std::vector<bool> convertBytesVectorToVector(const std::vector<unsigned char>& bytes);
uint64_t convertVectorToInt(const std::vector<bool>& v);

#endif // VOTECOIN_VOTECOIN_UTIL_H
