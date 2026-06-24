#pragma once

#include <chrono>
#include <iostream>
#include <string>

class Benchmark {
private:
    std::chrono::high_resolution_clock::time_point start_time;
public:
    Benchmark() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
    void stop(const std::string& operation, size_t input_size, size_t output_size = 0) {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        double seconds = duration / 1000.0;
        
        std::cout << "--- Benchmark Results ---\n";
        std::cout << "Operation: " << operation << "\n";
        std::cout << "Time elapsed: " << duration << " ms\n";
        
        if (seconds > 0) {
            double mb = (input_size / 1024.0 / 1024.0);
            std::cout << "Throughput: " << (mb / seconds) << " MB/s\n";
        }
        
        if (output_size > 0 && input_size > 0) {
            double ratio = static_cast<double>(output_size) / input_size * 100.0;
            std::cout << "Compression Ratio: " << ratio << "% (" 
                      << input_size << " bytes -> " << output_size << " bytes)\n";
        }
        std::cout << "-------------------------\n";
    }
};
