#include "bit_reader.hpp"
#include <stdexcept>

BitReader::BitReader(const std::string& filepath) : current_byte(0), bits_remaining(0) {
    file.open(filepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file for reading bits - " + filepath);
    }
}

BitReader::~BitReader() {
    if (file.is_open()) {
        file.close();
    }
}

std::unordered_map<unsigned char, uint64_t> BitReader::read_header() {
    std::unordered_map<unsigned char, uint64_t> freq_map;
    uint64_t size = 0;
    
    if (!file.read(reinterpret_cast<char*>(&size), sizeof(size))) {
        throw std::runtime_error("Error: Could not read header size.");
    }
    
    for (uint64_t i = 0; i < size; ++i) {
        unsigned char byte;
        uint64_t freq;
        if (!file.read(reinterpret_cast<char*>(&byte), sizeof(byte)) ||
            !file.read(reinterpret_cast<char*>(&freq), sizeof(freq))) {
            throw std::runtime_error("Error: Could not read header entry.");
        }
        freq_map[byte] = freq;
    }
    
    return freq_map;
}

bool BitReader::read_bit(bool& bit) {
    if (bits_remaining == 0) {
        if (!file.read(reinterpret_cast<char*>(&current_byte), 1)) {
            return false; // EOF reached
        }
        bits_remaining = 8;
    }
    
    // Read bit from MSB to LSB
    bit = (current_byte >> (bits_remaining - 1)) & 1;
    bits_remaining--;
    
    return true;
}
