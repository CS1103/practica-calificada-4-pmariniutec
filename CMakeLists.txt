cmake_minimum_required(VERSION 3.11)
project(PC4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread")

include_directories(.)

add_executable(PC4 catch.hpp main.cpp)
