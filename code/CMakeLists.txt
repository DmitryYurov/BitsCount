# CMake instructions to make the static lib
set(target_name bitscount)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")

add_library( ${target_name} STATIC ${headers} ${sources} )
set_target_properties(${target_name} PROPERTIES CXX_STANDARD 17)
if (AVX512)
	add_definitions(-DAVX512=${AVX512})
	target_compile_options(${target_name}
		PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive /arch:AVX512>"
			   "$<$<COMPILE_LANG_AND_ID:CXX,GNU>:-mavx512bitalg -march=native>"
			   "$<$<COMPILE_LANG_AND_ID:CXX,Clang>:-mavx512bitalg -march=native>"
	)
else()
target_compile_options(${target_name}
		PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->"
	)
endif()

target_link_libraries(${target_name})