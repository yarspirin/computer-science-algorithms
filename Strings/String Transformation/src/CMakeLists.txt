cmake_minimum_required(VERSION 3.5)
project(String_Transformation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set(SOURCE_FILES main.cpp)
# add_executable(String_Transformation ${SOURCE_FILES})

set(core_SRCS Transformer.cc)

add_library(core ${core_SRCS})
add_executable(exe main.cpp)
target_link_libraries(exe core)