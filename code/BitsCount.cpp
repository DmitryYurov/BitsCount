#include <array>

constexpr std::array<std::uint8_t, 256> makeLookupTable() {
    std::array<std::uint8_t, 256> result{ 0 };
    for (size_t i = 1; i < 256; ++i) {
        result[i] = (i & 1u) + result[i / 2u];
    }
    return result;
}

std::uint8_t bruteForce(std::uint32_t num) {
    std::uint8_t result = 0u;
    for (std::uint8_t i = 0; i < 32; ++i) {
        if (num & (1 << i)) ++result;
    }

    return result;
}

std::uint8_t algoKernighan(std::uint32_t num) {
    std::uint8_t result = 0;
    while (num) {
        num &= num - 1;
        ++result;
    }

    return result;
}

std::uint8_t lookupBytes(std::uint32_t num) {
    static constexpr std::array<std::uint8_t, 256> table = makeLookupTable();

    std::uint8_t result = 0u;
    for (std::uint8_t i = 0; i < 4; ++i) {
        result += table[(num >> 8 * i) & 0xff];
    }
    return result;
}

std::uint8_t divideAndConquer(std::uint32_t num) {
    num = (num & 0x55555555) + ((num >> 1) & 0x55555555);
    num = (num & 0x33333333) + ((num >> 2) & 0x33333333);
    num = (num & 0x0F0F0F0F) + ((num >> 4) & 0x0F0F0F0F);
    num = (num & 0x00FF00FF) + ((num >> 8) & 0x00FF00FF);
    num = (num & 0x0000FFFF) + (num >> 16);

    return static_cast<std::uint8_t>(num);
}
