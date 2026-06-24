#include <iostream>
#include <string>
#include <vector>
#include "io_utils.hpp"
#include "benchmark.hpp"
#include "huffman.hpp"
#include "bit_writer.hpp"

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
            
            if (!root) {
                std::cout << "Tree is empty (file might be empty).\n";
                return 0;
            }
            
            std::cout << "Generating prefix codes...\n";
            auto codes = Huffman::generate_codes(root.get());
            
            std::cout << "Compressing and writing to output file...\n";

            {
                BitWriter writer(output_file);
                writer.write_header(freq_map);

                std::ifstream in_file(input_file, std::ios::binary);
                if (!in_file.is_open()) {
                    throw std::runtime_error("Error: Could not open file for compression - " + input_file);
                }

                const size_t BUFFER_SIZE = 8192;
                std::vector<char> buffer(BUFFER_SIZE);

                while (in_file.read(buffer.data(), BUFFER_SIZE) || in_file.gcount() > 0) {
                    std::streamsize bytes_read = in_file.gcount();
                    for (std::streamsize i = 0; i < bytes_read; ++i) {
                        unsigned char byte = static_cast<unsigned char>(buffer[i]);
                        writer.write_bits(codes.at(byte));
                    }
                }

                writer.flush();
            } // BitWriter destructor closes the file before size measurement.

            std::ifstream orig_file(input_file, std::ios::binary | std::ios::ate);
            std::ifstream comp_file(output_file, std::ios::binary | std::ios::ate);

            size_t input_size = static_cast<size_t>(orig_file.tellg());
            size_t output_size = static_cast<size_t>(comp_file.tellg());

            const auto elapsed = bench.stop("Phase 3: Compression", input_size, output_size);
        }
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
