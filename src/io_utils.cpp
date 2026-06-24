#include "io_utils.hpp"
#include <fstream>
#include <stdexcept>

namespace IOUtils {

std::vector<uint8_t> read_file(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file for reading - " + filepath);
    }
    
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<uint8_t> buffer(size);
    if (size > 0 && !file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        throw std::runtime_error("Error: Failed to read from file - " + filepath);
    }
    
    return buffer;
}

void write_file(const std::string& filepath, const std::vector<uint8_t>& data) {
    std::ofstream file(filepath, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file for writing - " + filepath);
    }
    
    if (!data.empty() && !file.write(reinterpret_cast<const char*>(data.data()), data.size())) {
        throw std::runtime_error("Error: Failed to write to file - " + filepath);
    }
}

}
