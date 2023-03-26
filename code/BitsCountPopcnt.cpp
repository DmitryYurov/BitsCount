#include "BitsCountPopcnt.h"

#include <array>
#include <algorithm>
#include <bitset>
#include <immintrin.h>
#ifdef _MSC_VER
#include <intrin.h>
#endif
#include <iterator>


namespace {
bool hasPopcntSupport() {
#ifdef _MSC_VER
	std::array<int, 4> cpui = { 0 };

	__cpuid(cpui.data(), 0);
	if (cpui[0] < 1) return false;

	__cpuidex(cpui.data(), 1, 0);
	const std::bitset<32> ecx = cpui[2];

	return ecx[23];
#else
	__builtin_cpu_init();
	return __builtin_cpu_supports("popcnt");
#endif
}

#ifdef POPCNT

std::uint8_t popcnt(std::uint64_t num) {
	return static_cast<std::uint8_t>(_mm_popcnt_u64(num));
}

std::vector<std::uint8_t> BitsCountPopcntImpl(const std::vector<std::uint64_t>& nums) {
	std::vector<std::uint8_t> result;
	result.reserve(nums.size());
	std::transform(nums.begin(), nums.end(), std::back_inserter(result), popcnt);

	return result;
}
#endif
}

namespace bits_count::popcnt {

BitsCountPopcnt getFunc()
{
#ifdef POPCNT
	static auto func_ptr = hasPopcntSupport() ? &BitsCountPopcntImpl : nullptr;
	return func_ptr;
#else
	return nullptr;
#endif
}

}
