#include "BitsCount.h"

#include <array>
#include <algorithm>
#include <bit>
#include <bitset>
#include <iterator>

namespace {

constexpr std::array<std::uint8_t, 256> makeLookupTable() {
    std::array<std::uint8_t, 256> result{ 0 };
    for (std::size_t i = 1; i < 256; ++i) {
        result[i] = (i & 1u) + result[i / 2u];
    }
    return result;
}

inline std::uint8_t bruteForce(std::uint64_t num) {
    std::uint8_t result = 0u;
    for (std::uint8_t i = 0; i < 64; ++i)
        if (num & (UINT64_C(1) << i)) ++result;

    return result;
}

inline std::uint8_t algoKernighan(std::uint64_t num) {
    std::uint8_t result = 0;
    while (num) {
        num &= num - 1;
        ++result;
    }

    return result;
}

inline std::uint8_t lookupBytes(std::uint64_t num) {
    static constexpr std::array<std::uint8_t, 256> table = makeLookupTable();

    std::uint8_t result = table[num & 0xff];
    for (std::uint8_t i = 1; i < 8; ++i)
        result += table[(num >> 8u * i) & 0xffU];

    return result;
}

inline std::uint8_t divideAndConquer(std::uint64_t num) {
    num = (num & UINT64_C(0x5555555555555555)) + (num >> 1 & UINT64_C(0x5555555555555555));
    num = (num & UINT64_C(0x3333333333333333)) + (num >> 2 & UINT64_C(0x3333333333333333));
    num = (num & UINT64_C(0x0F0F0F0F0F0F0F0F)) + (num >> 4 & UINT64_C(0x0F0F0F0F0F0F0F0F));
    num = (num & UINT64_C(0x00FF00FF00FF00FF)) + (num >> 8 & UINT64_C(0x00FF00FF00FF00FF));
    num = (num & UINT64_C(0x0000FFFF0000FFFF)) + (num >> 16 & UINT64_C(0x0000FFFF0000FFFF));
    num = (num & UINT64_C(0x00000000FFFFFFFF)) + (num >> 32);

    return static_cast<std::uint8_t>(num);
}

inline std::uint8_t bitsetCount(std::uint64_t  num) {
    return static_cast<std::uint8_t>(std::bitset<64>(num).count());
}

inline std::uint8_t stdPopcnt(std::uint64_t nums) {
    return static_cast<std::uint8_t>(std::popcount(nums));
}

using BitCountType = std::uint8_t(*)(std::uint64_t);
template<BitCountType worker>
inline std::vector<std::uint8_t> vectorized(const std::vector<std::uint64_t>& nums) {
    std::vector<std::uint8_t> result;
    result.reserve(nums.size());
    std::transform(nums.begin(), nums.end(), std::back_inserter(result), [](auto item) { return worker(item); });

    return result;
}

}

namespace bits_count {

std::vector<std::uint8_t> bruteForce(const std::vector<std::uint64_t>& nums) { return vectorized<::bruteForce>(nums); }
std::vector<std::uint8_t> algoKernighan(const std::vector<std::uint64_t>& nums) {
    return vectorized<::algoKernighan>(nums);
}
std::vector<std::uint8_t> lookupBytes(const std::vector<std::uint64_t>& nums) { return vectorized<::lookupBytes>(nums); }
std::vector<std::uint8_t> divideAndConquer(const std::vector<std::uint64_t>& nums) { return vectorized<::divideAndConquer>(nums); }
std::vector<std::uint8_t> bitsetCount(const std::vector<std::uint64_t>& nums) { return vectorized<::bitsetCount>(nums); }
std::vector<std::uint8_t> stdPopcnt(const std::vector<std::uint64_t>& nums) { return vectorized<::stdPopcnt>(nums); }

}


