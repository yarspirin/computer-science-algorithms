cmake_minimum_required(VERSION 3.5)
project(Executor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Executor.cc)
add_executable(Executor ${SOURCE_FILES})