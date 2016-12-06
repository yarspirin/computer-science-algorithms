cmake_minimum_required(VERSION 3.5)
project(Pattern_Matching_with_Question_Marks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set(SOURCE_FILES main.cpp Trie.cc DeterministicFiniteAutomaton.cc Solver.cc)
# add_executable(Pattern_Matching_with_Question_Marks ${SOURCE_FILES})

set(core_SRCS DeterministicFiniteAutomaton.cc Solver.cc Trie.cc)

add_library(core ${core_SRCS})
add_executable(exe main.cpp)
target_link_libraries(exe core)