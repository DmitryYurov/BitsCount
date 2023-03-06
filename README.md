# BitsCount

A small repository with examples of how one can count set bits in an integer.
If you just want to get a gist of different methods of computing the set bits, just navigate to the `code` folder and look into `.cpp` files.

A detailed discussion of the algorithms' performance can be found in [this post](https://www.linkedin.com/pulse/how-many-ways-count-set-bits-do-you-know-dmitry-yurov%3FtrackingId=ShOvmbK6Yvc82SZ7psXA4w%253D%253D/?trackingId=ShOvmbK6Yvc82SZ7psXA4w%3D%3D).

## Requirements:
* C++20-capable compiler (mainly because of `std::popcount` function from `std`, all the rest can be compiled with `C++17`)
* With `AVX512` option: `avx512vpopcntdq`- and `popcnt`-capable hardware
* With `POPCNT` option: `popcnt`-capable hardware
* `CMake` ver. `>= 3.16`

## How to build:
Run `CMake` to generate project files. You can optionally pass the following arguments:
* `-DPOPCNT=ON`: enables using the `popcnt` instruction by the compiler
* `-DAVX512=ON`: enables vectorized `popcnt`, also enables the usual one (`POPCNT` flag is not necessary)

--------------
Tested on `x64` processor architecture with
* `gcc-10.3.0`
* `clang-13.0.1`
* `msvc-19.34.31937.0`
