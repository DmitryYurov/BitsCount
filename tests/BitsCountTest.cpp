#include <gtest/gtest.h>

#include <array>

#include "BitsCount.h"
#include "BitsCountAVX.h"
#include "BitsCountPopcnt.h"

static const std::vector<std::uint64_t> correctness_input{
	0xff,
	0xffff,
	0xf0f0,
	0x70607070,
	UINT64_C(0xff) << 56,
	UINT64_C(0xffffffffffffffff),
	0,
	1,
	UINT64_C(0xfe) << 55,
	UINT64_C(0xfe) << 54,
	UINT64_C(0xfe) << 53,
	UINT64_C(0xfe) << 52,
};

static const std::vector<std::uint8_t> correctness_expected{
	8, 16, 8, 11, 8, 64, 0, 1, 7, 7, 7, 7
};

TEST(Correcntess, BF)
{
	EXPECT_EQ(bits_count::bruteForce(correctness_input), correctness_expected);
}

TEST(Correcntess, Kernighan)
{
	EXPECT_EQ(bits_count::algoKernighan(correctness_input), correctness_expected);
}

TEST(Correcntess, Lookup)
{
	EXPECT_EQ(bits_count::lookupBytes(correctness_input), correctness_expected);
}

TEST(Correcntess, DQ)
{
	EXPECT_EQ(bits_count::divideAndConquer(correctness_input), correctness_expected);
}

TEST(Correctness, BitsetCount)
{
	EXPECT_EQ(bits_count::bitsetCount(correctness_input), correctness_expected);
}

TEST(Correctness, StdPopcnt)
{
	EXPECT_EQ(bits_count::stdPopcnt(correctness_input), correctness_expected);
}

TEST(Correcntess, Popcnt)
{
	auto bit_count_popcnt_func = bits_count::popcnt::getFunc();
	if (!bit_count_popcnt_func)
		GTEST_SKIP() << "POPCNT instruction is not supported by the hardware";
	EXPECT_EQ(bit_count_popcnt_func(correctness_input), correctness_expected);
}

TEST(Correctness, AVX) {
	auto bit_count_avx_func = bits_count::avx::getFunc();
	if (!bit_count_avx_func)
		GTEST_SKIP() << "Either the code has been compiled without AVX support or AVX is not supported by the hardware";

	EXPECT_EQ(bit_count_avx_func(correctness_input), correctness_expected);
}

static const auto perf_input = std::vector<std::uint64_t>(10000000u, 0xffU);

TEST(Performance, BF) {
	bits_count::bruteForce(perf_input);
}

TEST(Performance, Kernighan) {
	bits_count::algoKernighan(perf_input);
}

TEST(Performance, Lookup) {
	bits_count::lookupBytes(perf_input);
}

TEST(Performance, DQ) {
	bits_count::divideAndConquer(perf_input);
}

TEST(Performance, BitsetCount) {
	bits_count::bitsetCount(perf_input);
}

TEST(Performance, StdPopcnt) {
	bits_count::stdPopcnt(perf_input);
}

TEST(Performance, Popcnt) {
	auto bit_count_popcnt_func = bits_count::popcnt::getFunc();
	if (!bit_count_popcnt_func)
		GTEST_SKIP() << "POPCNT instruction is not supported by the hardware";

	bit_count_popcnt_func(perf_input);
}

TEST(Performance, AVX) {
	auto bit_count_avx_func = bits_count::avx::getFunc();
	if (!bit_count_avx_func)
		GTEST_SKIP() << "Either the code has been compiled without AVX support or AVX is not supported by the hardware";

	bit_count_avx_func(perf_input);
}
