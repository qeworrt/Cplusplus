cmake_minimum_required(VERSION 3.10.0)
project(typeList VERSION 0.1.0 LANGUAGES C CXX)

add_library(typeList typeList.cpp)

target_include_directories(typeList PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp)

target_link_libraries(main PRIVATE typeList)