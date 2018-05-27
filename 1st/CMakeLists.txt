cmake_minimum_required(VERSION 3.6)
project(Producer_consumer)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp cblock.h CBlockList.cpp CBlockList.h picosha2.h)
add_executable(Producer_consumer ${SOURCE_FILES})