cmake_minimum_required(VERSION 3.10)
project(HuffmanCompressor VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF) # Strict C++17

add_executable(huffman_compressor
    src/main.cpp
    src/io_utils.cpp
)
