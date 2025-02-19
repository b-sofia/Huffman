#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <bitset>
class Huffman {
public:
    Huffman();
    void decompress(const std::string& inputFile, const std::string& outputFile);
private:
struct Node {
        char symb;
        int freq;
        Node* left;
        Node* right;

        Node(char symb, int freq) : symb(symb), freq(freq), left(nullptr), right(nullptr) {}
    };
    struct Compare {
        bool operator()(Node* left, Node* right) {
            return left->freq > right->freq;
        }
    };
    std::map<char, int> countFrequencies(const std::string& data);
    Node* buildHuffmanTree(const std::map<char, int>& freqMap);
    void generateCodes(Node* root, std::string code, std::map<char, std::string>& huffmanCodes);
    std::string encodeData(const std::string& data, const std::map<char, std::string>& huffmanCodes);

    Node* deserializeTree(std::ifstream& inFile);

    std::string readCompressedData(const std::string& inputFile, Node*& root);

};  
#endif 