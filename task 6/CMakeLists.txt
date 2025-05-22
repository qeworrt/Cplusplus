cmake_minimum_required(VERSION 3.10)
project(CheckPointBuilder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(builder_example main.cpp CheckPoint.cpp Builders.cpp Processor.cpp)
