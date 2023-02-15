#ifndef __BITS_COUNT_AVX__
#define __BITS_COUNT_AVX__
#include <immintrin.h>

using BitsCountAvx = __m128i(*)(__m512i a);
BitsCountAvx getBitsCountAvx();

#endif
