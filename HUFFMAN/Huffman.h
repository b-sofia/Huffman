
#define HUFFMAN_H
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
class Huffman {
public:
    Huffman();
    void decompress(const std::string& inputFile, const std::string& outputFile);
    void compress(const std::string& inputFile, const std::string& outputFile);
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
    void writeCompressedData(const std::string& encodedData, Node* root, const std::string& outputFile);
    void serializeTree(Node* root, std::ofstream& outFile);

    Node* deserializeTree(std::ifstream& inFile);

    std::string readCompressedData(const std::string& inputFile, Node*& root);
    std::string decodeData(const std::string& encodedData, Node* root);

};  
