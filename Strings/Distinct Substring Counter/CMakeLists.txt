cmake_minimum_required(VERSION 3.5)
project(Distinct_Substring_Counter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SuffixArray.cc DistinctSubstringCounter.cc)
add_executable(Distinct_Substring_Counter ${SOURCE_FILES})