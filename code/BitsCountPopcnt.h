#ifndef __BITS_COUNT_POPCNT__
#define __BITS_COUNT_POPCNT__

#include <cstdint>
#include <vector>

namespace bits_count::popcnt {

using BitsCountPopcnt = std::vector<std::uint8_t>(*)(const std::vector<std::int64_t>&);
BitsCountPopcnt getFunc();

}

#endif
