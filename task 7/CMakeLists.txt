cmake_minimum_required(VERSION 3.10.0)
project(Bridge VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(Bridge main.cpp Set.h SetImpl.h ArraySetImpl.h HashSetImpl.h)