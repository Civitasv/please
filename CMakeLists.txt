cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(please)

add_subdirectory(lib)
add_subdirectory(include)
add_subdirectory(test)