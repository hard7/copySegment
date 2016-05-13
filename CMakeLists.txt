cmake_minimum_required(VERSION 3.4)
project(copySegment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic-errors")

set(SOURCE_FILES main.cpp detail/myPointTraits.cpp)
add_executable(copySegment ${SOURCE_FILES})