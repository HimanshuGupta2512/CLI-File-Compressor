#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace IOUtils {
    // Reads an entire file into a byte vector in strictly binary mode
    std::vector<uint8_t> read_file(const std::string& filepath);
    
    // Writes a byte vector to a file in strictly binary mode
    void write_file(const std::string& filepath, const std::vector<uint8_t>& data);
}
