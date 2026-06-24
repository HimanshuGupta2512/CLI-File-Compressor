#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>

class BitReader {
private:
    std::ifstream file;
    unsigned char current_byte;
    int bits_remaining;

public:
    explicit BitReader(const std::string& filepath);
    ~BitReader();

    std::unordered_map<unsigned char, uint64_t> read_header();
    bool read_bit(bool& bit);
    
    bool is_open() const { return file.is_open(); }
};
