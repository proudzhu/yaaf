cmake_minimum_required(VERSION 3.1.0)

project(yaaf CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(src)
add_subdirectory(tests)
