# High-Performance CLI File Compressor

![C++17](https://img.shields.io/badge/Language-Strict%20C%2B%2B17-blue) ![CMake](https://img.shields.io/badge/Build-CMake-green) ![Ninja](https://img.shields.io/badge/Generator-Ninja-black)

## Project Overview

* **Name**: High-Performance CLI File Compressor
* **Language**: Strict C++17 (Zero external dependencies, STL only)
* **Core Algorithm**: Huffman Coding with a deterministic prefix-tree architecture.

## Features

* **Lossless Round-Trip Guarantee**: Validated across edge cases including empty files, single-symbol repetitions, and full 100MB binary payloads.
* **Deterministic Tree Reconstruction**: Implemented a custom-tied min-heap comparator (min_byte tie-breaker) ensuring identical tree structures across varying platforms.
* **Memory Safety**: Built entirely using modern C++ smart pointers (`std::unique_ptr`), eliminating manual raw pointer deletions and preventing memory leaks.
* **Low-Level Bitwise Optimization**: Implemented a highly optimized `BitWriter` and `BitReader` class utilizing custom byte-packing and explicit OS stream flushing.

## Official Benchmark Performance

Tested against the industry-standard enwik8 dataset (100,000,000 bytes of raw text).

| Metric | Compression Phase | Decompression Phase |
| :--- | :--- | :--- |
| **Processing Time** | 3.865 seconds | 4.241 seconds |
| **Throughput Speed** | 25.87 MB/s | 23.58 MB/s |
| **Original File Size** | 100,000,000 bytes (100 MB) | — |
| **Output File Size** | 63,803,736 bytes (~63.8 MB) | 100,000,000 bytes (100 MB) |
| **Compression Ratio** | 63.80% | 100% Bit-Perfect Match |

## Build Instructions

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Usage Examples

```bash
# Compressing (-c)
./build/Release/huffman_compressor -c input.txt compressed.bin

# Decompressing (-d)
./build/Release/huffman_compressor -d compressed.bin restored_input.txt
```
