cmake_minimum_required(VERSION 3.5)
project(B_Puzzle_Solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp GameState.cc GameState.h CostInterface.h HeuristicInterface.h CoveredCost.cc CoveredCost.h ManhattanHeuristic.cc ManhattanHeuristic.h PuzzleSolver.cc PuzzleSolver.h)
add_executable(B_Puzzle_Solver ${SOURCE_FILES} GameState.cc GameState.h CostInterface.h HeuristicInterface.h CoveredCost.cc CoveredCost.h ManhattanHeuristic.cc ManhattanHeuristic.h PuzzleSolver.cc PuzzleSolver.h)