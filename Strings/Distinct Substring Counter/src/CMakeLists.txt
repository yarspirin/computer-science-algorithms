cmake_minimum_required(VERSION 3.5)
project(Distinct_Substring_Counter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# set(SOURCE_FILES main.cpp SuffixArray.cc DistinctSubstringCounter.cc)
# add_executable(Distinct_Substring_Counter ${SOURCE_FILES})

set(core_SRCS DistinctSubstringCounter.cc SuffixArray.cc)

add_library(core ${core_SRCS})
add_executable(exe main.cpp)
target_link_libraries(exe core)