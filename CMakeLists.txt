cmake_minimum_required (VERSION 3.13) 

project (kata)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra)

add_subdirectory(externals)
add_subdirectory(fizzbuzz)

