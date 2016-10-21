cmake_minimum_required(VERSION 3.5)
project(Graph_Traverser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Graph.hpp Traversal.hpp Tester.hpp)
add_executable(Graph_Traverser ${SOURCE_FILES})