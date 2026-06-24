#include "bit_writer.hpp"
#include <stdexcept>

BitWriter::BitWriter(const std::string& filepath) : current_byte(0), bit_count(0) {
    file.open(filepath, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file for writing bits - " + filepath);
    }
}

BitWriter::~BitWriter() {
    if (file.is_open()) {
        flush();
        file.close();
    }
}

void BitWriter::write_header(const std::unordered_map<unsigned char, uint64_t>& freq_map) {
    uint64_t size = freq_map.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    for (const auto& [byte, freq] : freq_map) {
        file.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
        file.write(reinterpret_cast<const char*>(&freq), sizeof(freq));
    }
}

void BitWriter::write_bit(bool bit) {
    if (bit) {
        current_byte |= (1 << (7 - bit_count));
    }
    bit_count++;
    
    if (bit_count == 8) {
        file.put(static_cast<char>(current_byte));
        current_byte = 0;
        bit_count = 0;
    }
}

void BitWriter::write_bits(const std::vector<bool>& bits) {
    for (bool b : bits) {
        write_bit(b);
    }
}

void BitWriter::flush() {
    if (bit_count > 0) {
        file.put(static_cast<char>(current_byte));
        current_byte = 0;
        bit_count = 0;
    }
    file.flush();
}
