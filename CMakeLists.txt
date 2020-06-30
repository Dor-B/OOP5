cmake_minimum_required(VERSION 3.12)
project(oop5)

set(CMAKE_CXX_STANDARD 11)

#add_executable(oop5 Part1Examples.cpp ListT.h Utilities.h MatrixOperations.h Stream.h)
#add_executable(oop5 Part2Examples.cpp Stream.h)
#add_executable(oop5 test2.cpp Stream.h)
#add_executable(oop5 main.cpp Stream.h)
add_executable(oop5 test1.cpp Utilities.h Transpose.h MatrixOperations.h)