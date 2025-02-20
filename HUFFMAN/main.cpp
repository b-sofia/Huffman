#include "huffman.h"

int main() {
    Huffman huffman;

    huffman.compress("input.txt", "compressed.bin");

    huffman.decompress("compressed.bin", "output.txt");

    return 0;
	
}