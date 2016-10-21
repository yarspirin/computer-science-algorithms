cmake_minimum_required(VERSION 3.5)
project(A_Trade_Arbitrage)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp TradeArbitrageSolver.cc TradeArbitrageSolver.h)
add_executable(A_Trade_Arbitrage ${SOURCE_FILES} TradeArbitrageSolver.cc TradeArbitrageSolver.h)