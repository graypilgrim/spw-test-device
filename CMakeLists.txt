cmake_minimum_required (VERSION 3.10)
project (SpaceWire_Test_Device)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 --std=c++17 -Wall -Wextra -pedantic")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread")

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable (spw-test-dev "${PROJECT_SOURCE_DIR}/src/main.cpp")

target_link_libraries (spw-test-dev SOURCE_OBJS)

add_subdirectory(src)
add_subdirectory(tests)
