#include "huffman.hpp"
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace Huffman {

std::unordered_map<unsigned char, uint64_t> build_frequency_map(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file for frequency mapping - " + filepath);
    }

    std::unordered_map<unsigned char, uint64_t> freq_map;
    const size_t BUFFER_SIZE = 8192;
    std::vector<char> buffer(BUFFER_SIZE);

    while (file.read(buffer.data(), BUFFER_SIZE) || file.gcount() > 0) {
        std::streamsize bytes_read = file.gcount();
        for (std::streamsize i = 0; i < bytes_read; ++i) {
            unsigned char byte = static_cast<unsigned char>(buffer[i]);
            freq_map[byte]++;
        }
    }

    return freq_map;
}

std::unique_ptr<HuffmanNode> build_huffman_tree(const std::unordered_map<unsigned char, uint64_t>& freq_map) {
    if (freq_map.empty()) {
        return nullptr;
    }

    std::vector<std::unique_ptr<HuffmanNode>> heap;
    heap.reserve(freq_map.size());
    
    for (const auto& [byte, freq] : freq_map) {
        heap.push_back(std::make_unique<HuffmanNode>(byte, freq));
    }

    auto comp = [](const std::unique_ptr<HuffmanNode>& a, const std::unique_ptr<HuffmanNode>& b) {
        return a->freq > b->freq; // min-heap means > operator
    };

    std::make_heap(heap.begin(), heap.end(), comp);

    while (heap.size() > 1) {
        std::pop_heap(heap.begin(), heap.end(), comp);
        std::unique_ptr<HuffmanNode> left = std::move(heap.back());
        heap.pop_back();

        std::pop_heap(heap.begin(), heap.end(), comp);
        std::unique_ptr<HuffmanNode> right = std::move(heap.back());
        heap.pop_back();

        heap.push_back(std::make_unique<HuffmanNode>(std::move(left), std::move(right)));
        std::push_heap(heap.begin(), heap.end(), comp);
    }

    return std::move(heap.front());
}

}
