cmake_minimum_required(VERSION 3.6)
project(untitled8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp merkle_tree.h merkle_tree.cpp picosha2.h)
add_executable(untitled8 ${SOURCE_FILES})