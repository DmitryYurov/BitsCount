#ifndef __BITS_COUNT__
#define __BITS_COUNT__

#include <cstdint>

std::uint8_t bruteForce(std::int64_t num);
std::uint8_t algoKernighan(std::int64_t num);
std::uint8_t lookupBytes(std::int64_t num);
std::uint8_t divideAndConquer(std::int64_t num);

#endif
