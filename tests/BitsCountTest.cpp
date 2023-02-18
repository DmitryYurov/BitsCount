#include <gtest/gtest.h>

#include <array>

#include "BitsCount.h"
#include "BitsCountAVX.h"

static const std::vector<std::int64_t> correctness_input{
	0xff,
	0xffff,
	0xf0f0,
	0x70607070,
	INT64_C(0xff) << 56,
	-1,
	0,
	1,
	INT64_C(0xfe) << 55,
	INT64_C(0xfe) << 54,
	INT64_C(0xfe) << 53,
	INT64_C(0xfe) << 52,
};

static const std::vector<std::uint8_t> correctness_expected{
	8, 16, 8, 11, 8, 64, 0, 1, 7, 7, 7, 7
};

TEST(BitsCountTest, CorrecntessBF)
{
	EXPECT_EQ(bits_count::bruteForce(correctness_input), correctness_expected);
}

TEST(BitsCountTest, CorrecntessKernighan)
{
	EXPECT_EQ(bits_count::algoKernighan(correctness_input), correctness_expected);
}

TEST(BitsCountTest, CorrecntessLookup)
{
	EXPECT_EQ(bits_count::lookupBytes(correctness_input), correctness_expected);
}

TEST(BitsCountTest, CorrecntessDQ)
{
	EXPECT_EQ(bits_count::divideAndConquer(correctness_input), correctness_expected);
}

TEST(BitsCountTest, CorrectnessAvx) {
	auto bit_count_avx_func = bits_count::avx::getFunc();
	if (!bit_count_avx_func)
		GTEST_SKIP() << "Either the code has been compiled without AVX support or AVX is not supported by the hardware";

	EXPECT_EQ(bit_count_avx_func(correctness_input), correctness_expected);
}
