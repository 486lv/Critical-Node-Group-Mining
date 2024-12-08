cmake_minimum_required(VERSION 3.30)
project(important_node)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8 -fexec-charset=UTF-8")

set(CMAKE_CXX_STANDARD 20)

add_executable(important_node main.cpp
)
