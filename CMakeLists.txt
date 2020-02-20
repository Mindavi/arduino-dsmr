cmake_minimum_required(VERSION 3.10)
project(DSMR)
set (CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra)
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(stdinreader)
add_subdirectory(fuzz)

