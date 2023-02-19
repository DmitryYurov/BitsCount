#include "BitsCountAVX.h"

#include <array>
#include <bitset>
#include <immintrin.h>
#include <cstring>
#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace {
inline bool hasAVXPopcntSupport() {
#ifdef _MSC_VER
	std::array<int, 4> cpui = { 0 };

	__cpuid(cpui.data(), 0);
	if (cpui[0] < 7) return false;

	__cpuidex(cpui.data(), 7, 0);
	const std::bitset<32> ecx = cpui[2];

	return ecx[14];
#else
	__builtin_cpu_init();
	return __builtin_cpu_supports("avx512vpopcntdq");
#endif
}

#ifdef AVX512
std::vector<std::uint8_t> BitsCountAVXImpl(const std::vector<std::int64_t>& nums) {
	const size_t nums_size = nums.size();
	auto result = std::vector<std::uint8_t>(nums_size, 0u);

	__m512i buf_avx;
	size_t i_item = 0;
	for (; i_item + 8 <= nums_size; i_item = i_item + 8) {
		buf_avx = _mm512_loadu_epi64(nums.data() + i_item);
		buf_avx = _mm512_popcnt_epi64(buf_avx);
		_mm_storeu_si64(result.data() + i_item, _mm512_cvtepi64_epi8(buf_avx));
	}

	// counting the bits in the rest of the input array
	if (i_item < nums_size) {
		std::array<std::int64_t, 8> in_buf = { 0 };
		std::memcpy(in_buf.data(), nums.data() + i_item, (nums_size - i_item) * 8);

		buf_avx = _mm512_loadu_epi64(in_buf.data());
		buf_avx = _mm512_popcnt_epi64(buf_avx);

		std::array<std::uint8_t, 8> ou_buf = { 0 };
		_mm_storeu_si64(ou_buf.data(), _mm512_cvtepi64_epi8(buf_avx));
		std::memcpy(result.data() + i_item, ou_buf.data(), nums_size - i_item);
	}

	return result;
}
#endif
}

namespace bits_count::avx {

BitsCountAvx getFunc()
{
#ifdef AVX512
	static auto func_ptr = hasAVXPopcntSupport() ? &BitsCountAVXImpl : nullptr;
	return func_ptr;
#else
	return nullptr;
#endif
}

}
