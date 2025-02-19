#include "Huffman.h"
Huffman::Huffman() {}
std::map<char, int> Huffman::countFrequencies(const std::string& data) {
    std::map<char, int> freqMap;
    for (char ch : data) {
        freqMap[ch]++;
    }
    return freqMap;
}               
Huffman::Node* Huffman::buildHuffmanTree(const std::map<char, int>& freqMap) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    for (auto& pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    return pq.top();
}
void Huffman::generateCodes(Node* root, std::string code, std::map<char, std::string>& huffmanCodes) {
    if (root == nullptr) return;
 
    if (root->symb != '\0') {
        huffmanCodes[root->symb] = code;
    }
 
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

std::string encodeData(const std::string& data, const std::map<char, std::string>& huffmanCodes) {
    std::string encodedData;
    for (char ch : data) {
        encodedData += huffmanCodes.at(ch);
    }
    return encodedData;
}

std::string Huffman::readCompressedData(const std::string& inputFile, Node*& root) {
 std::ifstream inFile(inputFile, std::ios::binary);
 if (!inFile) {
     std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
 return "";
    }
size_t dataSize;
inFile.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
root = deserializeTree(inFile);
std::string encodedData;
char byte;
while (inFile.get(byte)) {
     std::bitset<8> bits(byte);
     for (int i = 0; i < 8; ++i) {
        encodedData += (bits[i] ? '1' : '0');
     }
     }

encodedData.resize(dataSize);
inFile.close();
return encodedData;
    }  