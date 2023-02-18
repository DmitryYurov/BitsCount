#ifndef __BITS_COUNT__
#define __BITS_COUNT__

#include <cstdint>
#include <vector>

namespace bits_count {

std::vector<std::uint8_t> bruteForce(const std::vector<std::int64_t>& nums);
std::vector<std::uint8_t> algoKernighan(const std::vector<std::int64_t>& nums);
std::vector<std::uint8_t> lookupBytes(const std::vector<std::int64_t>& nums);
std::vector<std::uint8_t> divideAndConquer(const std::vector<std::int64_t>& nums);

}

#endif
