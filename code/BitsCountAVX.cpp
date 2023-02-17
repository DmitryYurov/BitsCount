#include "BitsCountAVX.h"

#include <array>
#include <bitset>
#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace {
	inline bool hasAVXBitalgSupport() {
#ifdef _MSC_VER
		std::array<int, 4> cpui = { 0 };

		__cpuid(cpui.data(), 0);
		if (cpui[0] < 7) return false;

		__cpuidex(cpui.data(), 7, 0);
		const std::bitset<32> ecx = cpui[2];

		return ecx[12];
#else
		__builtin_cpu_init();
		return __builtin_cpu_supports("avx512bitalg");
#endif
	}

#ifdef AVX512
	__m128i BitsCountAVXImpl(__m512i num) {
		__m512i a = _mm512_popcnt_epi64(num);
		return _mm_cvtepi8_epi16(_mm512_cvtepi64_epi8(a));
	}
#endif
}

BitsCountAvx getBitsCountAvx()
{
#ifdef AVX512
	return hasAVXBitalgSupport() ? &BitsCountAVXImpl : nullptr;
#else
	return nullptr;
#endif
}
