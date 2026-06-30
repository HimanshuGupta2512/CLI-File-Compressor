# High-Performance CLI File Compressor 🚀

![C++17](https://img.shields.io/badge/C++-17-blue.svg) ![CMake](https://img.shields.io/badge/CMake-Build-green.svg) ![Dependencies](https://img.shields.io/badge/Dependencies-Zero-brightgreen.svg)

A high-performance, strictly C++17 command-line utility for text and binary file compression. Built entirely on the Standard Template Library (STL) with zero external dependencies, this tool implements a custom, highly optimized Huffman Coding algorithm featuring deterministic prefix-tree architecture and robust bit-level serialization.

## 🌟 Key Features & Architectural Highlights

*   **Lossless Round-Trip Guarantee**: Rigorously validated across extreme edge cases, including completely empty files, single-symbol repetitions, and full 100MB binary payloads without corruption.
*   **Deterministic Tree Reconstruction**: Implemented a custom-tied min-heap comparator (with a `min_byte` tie-breaker) to guarantee mathematically identical tree structures across varying platforms and compiler architectures.
*   **Memory Safety & RAII**: Built entirely using modern C++ smart pointers (`std::unique_ptr`). This eliminates manual raw pointer deletions and definitively prevents memory leaks during deep tree traversals.
*   **Low-Level Bitwise Optimization**: Engineered custom `BitWriter` and `BitReader` classes utilizing tight bitwise packing (`<<`, `>>`, `|`) and explicit OS-level stream flushing to maximize I/O throughput.

## 📊 Official Benchmark Performance

Tested against the industry-standard **enwik8 dataset** (100,000,000 bytes of raw text).

| Metric | Compression Phase | Decompression Phase |
| :--- | :--- | :--- |
| **Processing Time** | 3.865 seconds | 4.241 seconds |
| **Throughput Speed** | 25.87 MB/s | 23.58 MB/s |
| **Original File Size** | 100,000,000 bytes (100 MB) | — |
| **Output File Size** | 63,803,736 bytes (~63.8 MB) | 100,000,000 bytes (100 MB) |
| **Compression Ratio** | **63.80%** | **100% Bit-Perfect Match** |

## 🛠️ Build Instructions

This project strictly enforces C++17 and relies on CMake for cross-platform building. To compile a high-performance Release build, execute the following commands:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## 💻 Usage Examples

The resulting executable `huffman_compressor` can be utilized directly from the command line.

**Compress a file (`-c` flag):**
```bash
./build/Release/huffman_compressor -c input.txt compressed.bin
```

**Decompress an archive (`-d` flag):**
```bash
./build/Release/huffman_compressor -d compressed.bin restored_input.txt
```
