#include <iostream>
#include <string>
#include <vector>
#include "io_utils.hpp"
#include "benchmark.hpp"

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
        
        // For Phase 1, we just test binary I/O (copying file directly)
        std::cout << "Reading input file...\n";
        std::vector<uint8_t> data = IOUtils::read_file(input_file);
        size_t input_size = data.size();
        
        std::cout << "Writing output file...\n";
        // To test I/O correctness, we write the data exactly as read.
        IOUtils::write_file(output_file, data);
        size_t output_size = data.size();
        
        bench.stop("Phase 1: I/O Copy", input_size, output_size);
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
