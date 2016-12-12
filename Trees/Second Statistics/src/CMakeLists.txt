cmake_minimum_required(VERSION 3.5)
project(Second_Statistics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set(SOURCE_FILES main.cpp SegmentTree.cc SegmentTree.h)
# add_executable(Second_Statistics ${SOURCE_FILES})

set(core_SRCS main.cpp SegmentTree.cc)

add_library(core ${core_SRCS})
add_executable(exe main.cpp)
target_link_libraries(exe core)
