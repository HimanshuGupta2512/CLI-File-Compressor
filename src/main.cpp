#include <iostream>
#include <string>
#include <vector>
#include "io_utils.hpp"
#include "benchmark.hpp"
#include "huffman.hpp"

void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " <mode> <input_file> <output_file>\n"
              << "Modes:\n"
              << "  -c  Compress\n"
              << "  -d  Decompress\n";
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }

    std::string mode = argv[1];
    std::string input_file = argv[2];
    std::string output_file = argv[3];

    if (mode != "-c" && mode != "-d") {
        std::cerr << "Invalid mode. Use -c for compress or -d for decompress.\n";
        print_usage(argv[0]);
        return 1;
    }

    try {
        Benchmark bench;
        
        if (mode == "-c") {
            std::cout << "Building frequency map...\n";
            auto freq_map = Huffman::build_frequency_map(input_file);
            std::cout << "Unique bytes found: " << freq_map.size() << "\n";
            
            std::cout << "Constructing Huffman tree...\n";
            auto root = Huffman::build_huffman_tree(freq_map);
            
            if (root) {
                std::cout << "Root node frequency (total bytes): " << root->freq << "\n";
            } else {
                std::cout << "Tree is empty (file might be empty).\n";
            }
            
            std::cout << "Reading input file for copy...\n";
            std::vector<uint8_t> data = IOUtils::read_file(input_file);
            size_t input_size = data.size();
            
            std::cout << "Writing output file...\n";
            IOUtils::write_file(output_file, data);
            size_t output_size = data.size();
            
            const auto elapsed = bench.stop("Phase 2: Tree Construction", input_size, output_size);
        }
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
