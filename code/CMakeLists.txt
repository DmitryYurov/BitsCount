# CMake instructions to make the static lib
set(target_name bitscount)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")

add_library( ${target_name} STATIC ${headers} ${sources} )
set_target_properties(${target_name} PROPERTIES CXX_STANDARD 20)
if (AVX512)
	add_definitions(-DAVX512=${AVX512})
	add_definitions(-DPOPCNT=${POPCNT})
	target_compile_options(${target_name}
		PRIVATE "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->"
		PRIVATE "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/arch:AVX512>"
		PRIVATE "$<$<COMPILE_LANG_AND_ID:CXX,GNU>:-mavx512vpopcntdq>"
		PRIVATE "$<$<COMPILE_LANG_AND_ID:CXX,Clang>:-mavx512vpopcntdq>"
	)
elseif (POPCNT)
	add_definitions(-DPOPCNT=${POPCNT})
	target_compile_options(${target_name}
		PRIVATE "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->"
		PRIVATE "$<$<COMPILE_LANG_AND_ID:CXX,GNU>:-mpopcnt>"
		PRIVATE "$<$<COMPILE_LANG_AND_ID:CXX,Clang>:-mpopcnt>"
	)
else()
	target_compile_options(${target_name}
		PRIVATE "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->"
	)
endif()

target_link_libraries(${target_name})