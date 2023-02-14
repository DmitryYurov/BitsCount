# CMake instructions to make the static lib
set(target_name bitscount)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")

add_library( ${target_name} STATIC ${headers} ${sources} )
set_target_properties(${target_name} PROPERTIES CXX_STANDARD 17)
target_compile_options(${target_name} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")
# target_include_directories(
#  ${target_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
# )

target_link_libraries(${target_name})