cmake_minimum_required(VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


project(FlipFlop)
set(PROJECT_NAME FlipFlop)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/project/"
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/json/"
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

# link all .lib files
file(GLOB_RECURSE LIB_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.lib")
foreach(LIB_FILE ${LIB_FILES})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_FILE})
endforeach()

# copy all dlls to output directory
file(GLOB_RECURSE DLL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.dll")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${DLL_FILES} 
	$<TARGET_FILE_DIR:${PROJECT_NAME}>
)