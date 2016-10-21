cmake_minimum_required(VERSION 3.5)
project(C_Distance_Calculator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp DistanceCalculator.hpp GraphStorageFactory.hpp)
add_executable(C_Distance_Calculator ${SOURCE_FILES} DistanceCalculator.hpp GraphStorageFactory.hpp)