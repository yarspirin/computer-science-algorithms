cmake_minimum_required(VERSION 3.5)
project(Hamming_distance)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set(SOURCE_FILES main.cpp Solver.cc)
# add_executable(Hamming_distance ${SOURCE_FILES})

set(core_SRCS main.cpp Solver.cc)

add_library(core ${core_SRCS})
add_executable(exe main.cpp)
target_link_libraries(exe core)