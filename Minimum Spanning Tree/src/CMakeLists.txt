cmake_minimum_required(VERSION 3.5)
project(MST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(core_SRCS main.cpp MinSpanningTreeFinderInterface.hpp PrimMSTFinder.hpp KruskalMSTFinder.hpp BoruvkaMSTFinder.hpp Graph.hpp Edge.hpp DisjointSetUnion.cc DisjointSetUnion.h)

add_library(core ${core_SRCS})

add_executable(exe ${core_SRCS})
target_link_libraries(exe core)

# set(SOURCE_FILES main.cpp MinSpanningTreeFinderInterface.hpp PrimMSTFinder.hpp KruskalMSTFinder.hpp BoruvkaMSTFinder.hpp Graph.hpp Edge.hpp DisjointSetUnion.cc DisjointSetUnion.h)
# add_executable(MST ${SOURCE_FILES})