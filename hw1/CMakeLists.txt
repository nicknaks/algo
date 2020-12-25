cmake_minimum_required(VERSION 3.17)
project(hw1)

set(CMAKE_CXX_STANDARD 17)

set(graphs ListGraph.cpp MatrixGraph.cpp SetGraph.cpp ArcGraph.cpp main.cpp)

add_executable(hw1 ${graphs})