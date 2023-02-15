#include <gtest/gtest.h>

#include <array>

#include "BitsCount.h"
#include "BitsCountAVX.h"

TEST(BitsCountTest, Correctness)
{
	EXPECT_EQ(bruteForce(0xff), 8);
	EXPECT_EQ(bruteForce(0xffff), 16);
	EXPECT_EQ(bruteForce(0xf0f0), 8);
	EXPECT_EQ(bruteForce(0x70607070), 11);
	EXPECT_EQ(bruteForce(INT64_C(0xff) << 56), 8);

	EXPECT_EQ(algoKernighan(0xff), 8);
	EXPECT_EQ(algoKernighan(0xffff), 16);
	EXPECT_EQ(algoKernighan(0xf0f0), 8);
	EXPECT_EQ(algoKernighan(0x70607070), 11);
	EXPECT_EQ(algoKernighan(INT64_C(0xff) << 56), 8);

	EXPECT_EQ(lookupBytes(0xff), 8);
	EXPECT_EQ(lookupBytes(0xffff), 16);
	EXPECT_EQ(lookupBytes(0xf0f0), 8);
	EXPECT_EQ(lookupBytes(0x70607070), 11);
	EXPECT_EQ(lookupBytes(INT64_C(0xff) << 56), 8);

	EXPECT_EQ(divideAndConquer(0xff), 8);
	EXPECT_EQ(divideAndConquer(0xffff), 16);
	EXPECT_EQ(divideAndConquer(0xf0f0), 8);
	EXPECT_EQ(divideAndConquer(0x70607070), 11);
	EXPECT_EQ(divideAndConquer(INT64_C(0xff) << 56), 8);
}

TEST(BitsCountTest, CorrectnessAvx) {
	auto bit_count_avx_func = getBitsCountAvx();
	if (!bit_count_avx_func)
		GTEST_SKIP() << "Either the code has been compiled without AVX support or AVX is not supported by the hardware";

	auto input = _mm512_set_epi64(0xff, 0xffff, 0xf0f0, 0x70607070, INT64_C(0xff) << 56, INT64_C(0xffffffffffffffff), 0, 0x01);
	//							  e7	e6		e5		e4			e3					 e2							  e1 e0
	auto avx_result = bit_count_avx_func(input);
	std::array<std::uint16_t, 8> result;
	_mm_storeu_epi16(result.data(), avx_result);
	std::array<std::uint16_t, 8> expected = { 1, 0, 64, 8, 11, 8, 16, 8};
	//										  e0 e1 e2  e3 e4  e5 e6  e7
	EXPECT_EQ(result, expected);
}
