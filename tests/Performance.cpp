#include <gtest/gtest.h>

#include <array>
#include <numeric>
#include <chrono>
#include <limits>
#include <random>
#include <iostream>

#include "BitsCount.h"
#include "BitsCountAVX.h"
#include "BitsCountPopcnt.h"

namespace {
std::vector<std::uint64_t> createPerformanceInput() {
	constexpr size_t vec_size = 10000000u;
	constexpr std::uint64_t seed = UINT64_C(1676825615);
	std::mt19937_64 rng(seed);

	std::uniform_int_distribution<std::mt19937_64::result_type> dist(0, std::numeric_limits<std::uint64_t>::max());

	std::vector<std::uint64_t> result(vec_size, 0u);
	for (size_t i = 0; i < vec_size; ++i)
		result[i] = dist(rng);

	return result;
}

using Method = std::vector<std::uint8_t>(*)(const std::vector<std::uint64_t>&);
void measurePerformance(Method method) {
	using std::chrono::high_resolution_clock;
	using std::chrono::duration;

	constexpr size_t n_runs = 400;
	static const auto input = createPerformanceInput();

	method(input); // skipping the first run

	std::array<double, n_runs> durations_us = { 0 };
	for (size_t i = 0; i < n_runs; ++i) {
		const auto t1 = high_resolution_clock::now();
		method(input);
		const auto t2 = high_resolution_clock::now();
		durations_us[i] = duration<double, std::micro>(t2 - t1).count();
	}
	const double mean_us = std::accumulate(durations_us.begin(), durations_us.end(), 0.0,
										   [](double sum, double item) { return sum + item; }) / n_runs;
	const double stddev = std::sqrt(std::accumulate(durations_us.begin(), durations_us.end(), 0.0,
													[mean_us](double sum, double item) {
														return sum + (item - mean_us) * (item - mean_us);
													}) / (n_runs - 1)
									);

	std::cout << "Execution has taken " << (mean_us * 1.e-3) << " ms per run" << std::endl;
	std::cout << "With standard deviation " << (stddev * 1.e-3) << std::endl;
}

}

TEST(Performance, BF) {
	measurePerformance(bits_count::bruteForce);
}

TEST(Performance, Kernighan) {
	measurePerformance(bits_count::algoKernighan);
}

TEST(Performance, Lookup) {
	measurePerformance(bits_count::lookupBytes);
}

TEST(Performance, DQ) {
	measurePerformance(bits_count::divideAndConquer);
}

TEST(Performance, BitsetCount) {
	measurePerformance(bits_count::bitsetCount);
}

TEST(Performance, StdPopcnt) {
	measurePerformance(bits_count::stdPopcnt);
}

TEST(Performance, Popcnt) {
	auto bit_count_popcnt_func = bits_count::popcnt::getFunc();
	if (!bit_count_popcnt_func)
		GTEST_SKIP() << "POPCNT instruction is not supported by the hardware or manually disabled";

	measurePerformance(bit_count_popcnt_func);
}

TEST(Performance, AVX) {
	auto bit_count_avx_func = bits_count::avx::getFunc();
	if (!bit_count_avx_func)
		GTEST_SKIP() << "Either the code has been compiled without AVX support or AVX is not supported by the hardware";

	measurePerformance(bit_count_avx_func);
}
