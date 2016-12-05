cmake_minimum_required(VERSION 3.5)
project(Tree_Comparator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set(SOURCE_FILES main.cpp BinarySearchTree.cc BinarySearchTree.h CartesianTree.cc CartesianTree.h)
# add_executable(Tree_Comparator ${SOURCE_FILES})

set(core_SRCS BinarySearchTree.cc CartesianTree.cc)

add_library(core ${core_SRCS})
add_executable(exe main.cpp)
target_link_libraries(exe core)