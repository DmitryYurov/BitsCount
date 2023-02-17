#ifndef __BITS_COUNT_AVX__
#define __BITS_COUNT_AVX__

#include <cstdint>
#include <vector>

namespace bits_count::avx {

using BitsCountAvx = std::vector<std::uint8_t>(*)(const std::vector<std::int64_t>&);
BitsCountAvx getFunc();

}

#endif
