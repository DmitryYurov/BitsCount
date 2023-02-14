set(target_name tests)
include(CTest)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(
  ${target_name}
  BitsCountTest.cpp
)
target_include_directories(${target_name} PRIVATE "../code")
target_link_libraries(
  ${target_name}
  PRIVATE
  bitscount
  PUBLIC
  GTest::gtest_main
)

gtest_discover_tests(${target_name})
