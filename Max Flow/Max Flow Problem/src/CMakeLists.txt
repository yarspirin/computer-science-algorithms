cmake_minimum_required(VERSION 3.5)
project(Max_Flow_Problem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set(SOURCE_FILES main.cpp Graph.cc)
# add_executable(Max_Flow_Problem ${SOURCE_FILES})

set(core_SRCS main.cpp Graph.cc)

add_library(core ${core_SRCS})
add_executable(exe ${core_SRCS})
target_link_libraries(exe core)