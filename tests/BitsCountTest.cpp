#include <gtest/gtest.h>

#include "BitsCount.h"

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
