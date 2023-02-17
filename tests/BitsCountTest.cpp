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
	auto bit_count_avx_func = bits_count::avx::getFunc();
	if (!bit_count_avx_func)
		GTEST_SKIP() << "Either the code has been compiled without AVX support or AVX is not supported by the hardware";

	std::vector<std::int64_t> input{
		0xff, 0xffff, 0xf0f0, 0x70607070, INT64_C(0xff) << 56, -1, 0, 1, // 8 * 64 bits
		0xff, 0xffff, 0xf0f0, 0x70607070 // 4 * 64 bits
	};
	auto actual = bit_count_avx_func(input);
	std::vector<std::uint8_t> expected{ 8, 16, 8, 11, 8, 64, 0, 1, 8, 16, 8, 11 };
	EXPECT_EQ(actual, expected);
}
