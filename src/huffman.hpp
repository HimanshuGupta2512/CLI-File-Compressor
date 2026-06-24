#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <cstdint>

struct HuffmanNode {
    unsigned char byte;
    uint64_t freq;
    std::unique_ptr<HuffmanNode> left;
    std::unique_ptr<HuffmanNode> right;
    
    // Leaf node constructor
    HuffmanNode(unsigned char b, uint64_t f) : byte(b), freq(f), left(nullptr), right(nullptr) {}
    
    // Internal node constructor
    HuffmanNode(std::unique_ptr<HuffmanNode> l, std::unique_ptr<HuffmanNode> r)
        : byte(0), freq(l->freq + r->freq), left(std::move(l)), right(std::move(r)) {}
};

namespace Huffman {
    // Reads file block-by-block and computes byte frequencies
    std::unordered_map<unsigned char, uint64_t> build_frequency_map(const std::string& filepath);
    
    // Constructs the Huffman tree using a min-heap
    std::unique_ptr<HuffmanNode> build_huffman_tree(const std::unordered_map<unsigned char, uint64_t>& freq_map);

    // Generates Huffman codes from the tree
    using CodeMap = std::unordered_map<unsigned char, std::vector<bool>>;
    CodeMap generate_codes(const HuffmanNode* root);
}
