#include "BitsCount.h"

#include <array>

constexpr std::array<std::uint8_t, 256> makeLookupTable() {
    std::array<std::uint8_t, 256> result{ 0 };
    for (std::size_t i = 1; i < 256; ++i) {
        result[i] = (i & 1u) + result[i / 2u];
    }
    return result;
}

std::uint8_t bruteForce(std::int64_t num) {
    std::uint8_t result = 0u;
    for (std::uint8_t i = 0; i < 64; ++i)
        if (num & (INT64_C(1) << i)) ++result;

    return result;
}

std::uint8_t algoKernighan(std::int64_t num) {
    std::uint8_t result = 0;
    while (num) {
        num &= num - 1;
        ++result;
    }

    return result;
}

std::uint8_t lookupBytes(std::int64_t num) {
    static constexpr std::array<std::uint8_t, 256> table = makeLookupTable();

    std::uint8_t result = table[num & 0xff];
    for (std::uint8_t i = 1; i < 8; ++i)
        result += table[(num >> 8u * i) & 0xff];

    return result;
}

std::uint8_t divideAndConquer(std::int64_t num) {
    num = (num & INT64_C(0x5555555555555555)) + ((num >> 1) & INT64_C(0x5555555555555555));
    num = (num & INT64_C(0x3333333333333333)) + ((num >> 2) & INT64_C(0x3333333333333333));
    num = (num & INT64_C(0x0F0F0F0F0F0F0F0F)) + ((num >> 4) & INT64_C(0x0F0F0F0F0F0F0F0F));
    num = (num & INT64_C(0x00FF00FF00FF00FF)) + ((num >> 8) & INT64_C(0x00FF00FF00FF00FF));
    num = (num & INT64_C(0x0000FFFF0000FFFF)) + ((num >> 16) & INT64_C(0x0000FFFF0000FFFF));
    num = (num & INT64_C(0x00000000FFFFFFFF)) + (num >> 32);

    return static_cast<std::uint8_t>(num);
}
