cmake_minimum_required(VERSION 3.10.0)
project(mixin VERSION 0.1.0 LANGUAGES C CXX)

add_library(mixin mixins.cpp)

target_include_directories(mixin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp)

target_link_libraries(main PRIVATE mixin)
