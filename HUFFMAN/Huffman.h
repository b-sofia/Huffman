#include <iostream>
#include <fstream>
#include <map>
class Huffman {
public:

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

};   