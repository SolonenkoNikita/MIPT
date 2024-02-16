cmake_minimum_required(VERSION 3.16)
project(vector)

set(CMAKE_CXX_STANDARD 20)

add_library (vector INTERFACE)

target_include_directories(vector INTERFACE include)
