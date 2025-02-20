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



void Huffman::writeCompressedData(const std::string& encodedData, Node* root, const std::string& outputFile) {
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
      size_t dataSize = encodedData.size();
      outFile.write(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));   
      serializeTree(root, outFile);
      std::bitset<8> byte;
      int bitCount = 0;
      for (char bit : encodedData) {
          byte[bitCount++] = (bit == '1');
          if (bitCount == 8) {
              outFile.put(static_cast<char>(byte.to_ulong()));
              byte.reset();
              bitCount = 0;
          }
      }
    if (bitCount > 0) {
        outFile.put(static_cast<char>(byte.to_ulong()));
    } 
    outFile.close();
}



std::string encodeData(const std::string& data, const std::map<char, std::string>& huffmanCodes) {
    std::string encodedData;
    for (char ch : data) {
        encodedData += huffmanCodes.at(ch);
    }
    return encodedData;
}


void Huffman::serializeTree(Node* root, std::ofstream& outFile) {
    if (root == nullptr) {
        outFile.put(0);
        return;
    }

    outFile.put(1);
    outFile.put(root->symb);
    outFile.write(reinterpret_cast<char*>(&root->freq), sizeof(root->freq));

    serializeTree(root->left, outFile);
    serializeTree(root->right, outFile);
}


Huffman::Node* Huffman::deserializeTree(std::ifstream& inFile) {
    char marker;
    inFile.get(marker);

    if (marker == 0) {
        return nullptr;
    }

    char symb;
    inFile.get(symb);

    int freq;
    inFile.read(reinterpret_cast<char*>(&freq), sizeof(freq));

    Node* node = new Node(symb, freq);
    node->left = deserializeTree(inFile);
    node->right = deserializeTree(inFile);

    return node;
}


std::string Huffman::readCompressedData(const std::string& inputFile, Node*& root) {
 std::ifstream inFile(inputFile, std::ios::binary);
 if (!inFile) {
     std::cerr << "Error of openning file to reading!" << std::endl;
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

std::string Huffman::decodeData(const std::string& encodedData, Node* root) {
    std::string decodedData;
    Node* current = root;
    for (char bit : encodedData) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
    
        if (current->symb != '\0') {
            decodedData += current->symb;
            current = root;
        }
    }
    return decodedData;
}

void Huffman::decompress(const std::string& inputFile, const std::string& outputFile) {
    Node* root = nullptr;
    std::string encodedData = readCompressedData(inputFile, root);
    std::string decodedData = decodeData(encodedData, root);
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error of openning file to writing!" << std::endl;
        return;
    }
 
    outFile << decodedData;
    outFile.close();
 
    std::cout << "File has been successfully unpacked and saved to " << outputFile << std::endl;
}
void Huffman::compress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error opening the file for reading!" << std::endl;
        return;
    }
    std::string data((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();
    std::map<char, int> freqMap = countFrequencies(data);

    Node* root = buildHuffmanTree(freqMap);

    std::map<char, std::string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    std::string encodedData = encodeData(data, huffmanCodes);

    writeCompressedData(encodedData, root, outputFile);

    std::cout << "File has been successfully compressed and saved to " << outputFile << std::endl;
}
std::string Huffman::encodeData(const std::string& data, const std::map<char, std::string>& huffmanCodes) {
    std::string encodedData;
    for (char ch : data) {
        encodedData += huffmanCodes.at(ch);
    }
    return encodedData;
}