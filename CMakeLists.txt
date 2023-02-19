cmake_minimum_required(VERSION 3.16)
project(
	BitsCount
	VERSION 0.0.0
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
add_subdirectory(code)
add_subdirectory(tests)
