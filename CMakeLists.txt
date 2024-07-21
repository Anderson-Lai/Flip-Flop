cmake_minimum_required(VERSION 3.28)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# target vcpkg
if (DEFINED ENV{VCPKG_ROOT_DIRECTORY})
	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT_DIRECTORY}/scripts/buildsystems/vcpkg.cmake")
else ()
	message(FATAL_ERROR "Environment variable VCPKG_ROOT_DIRECTORY is not defined. Point it to where vcpkg is installed")
endif()

# project name
project(FlipFlop)
set(PROJECT_NAME FlipFlop)

# set c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# dependencies
find_package(wxWidgets REQUIRED COMPONENTS core base)
find_package(CURL REQUIRED)

# get the cmake script provided by wxWidgets
include(${wxWidgets_USE_FILE})

# adding .cpp files
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp")
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})

# adding .h and .hpp files
target_include_directories(${PROJECT_NAME} 
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/project/"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/json/"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/"
        "${wxWidgets_INCLUDE_DIRS}"
)

# linking libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES} CURL::libcurl)
