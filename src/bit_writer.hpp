#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>

class BitWriter {
private:
    std::ofstream file;
    unsigned char current_byte;
    int bit_count;

public:
    explicit BitWriter(const std::string& filepath);
    ~BitWriter();

    void write_header(const std::unordered_map<unsigned char, uint64_t>& freq_map);
    void write_bit(bool bit);
    void write_bits(const std::vector<bool>& bits);
    void flush();
    
    bool is_open() const { return file.is_open(); }
};
