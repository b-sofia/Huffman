#include "huffman.h"
Huffman::Huffman() {}
std::map<char, int> Huffman::countFrequencies(const std::string& data) {
    std::map<char, int> freqMap;
    for (char ch : data) {
        freqMap[ch]++;
    }
    return freqMap;
}