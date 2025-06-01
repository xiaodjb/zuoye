/*********************************************************** 
 * CS111 OOP 2025 Homework 2 
 * Program designed and implemented by the instructor
 * Zhiyao Liang  ( zyliang@must.edu.mo )                                
 * Date: 2025-May                                       
 ***********************************************************/

  /*******************************************
  * If you changed the file, write your names
  * Student names: 
  ********************************************/

#ifndef _HUFFMAN_ALGORITHM_HPP_
#define _HUFFMAN_ALGORITHM_HPP_

#include "huffman_tree.hpp"
#include "../../IO/Bit_stream/bit_stream.hpp"

#include <string>

typedef std::unordered_map<char, int> FrequencyMap;
typedef std::unordered_map<char, std::vector<bool>> EncodingTable;
typedef std::vector<bool> BitVector;
typedef std::unordered_map<std::vector<bool>, char> DecodingTable;

// Function to build the Huffman tree from a frequency map, 
// it returns the number of unique characters in the string text.  
int string_to_frequence_map(const std::string& text, FrequencyMap& freq_map);

// Function to build the Huffman tree from a frequency map
void huffman_tree_to_encoding_table(const HuffmanTree& tree, EncodingTable& encoding_table);

class HuffmanEncoder {
    const HuffmanTree& tree;
    EncodingTable encoding_table;  
    //void build_table(const HuffmanNode* node, std::vector<bool> prefix);
public:
    explicit HuffmanEncoder(const HuffmanTree& t);
    void encode(BitStream& bos, const std::string& text); // the compress function
};

class HuffmanDecoder {
    const HuffmanTree& tree;

    // The following member is not used. 
    // size_t current_pos = 0; 
    /* Current position in the bit stream. It is needed because the bits are read one by one.
    */ 

    // The encoding table is not needed for the decoder, because the tree is already built.
     
public:
    explicit HuffmanDecoder(const HuffmanTree& t);
    std::string decode(BitStream& bis); // the decompress function. Decode the whole bit stream.

    // Can possibly define a decode function where the starting and ending positions are passed as arguments. 
    // This function will be used to decode a part of the bit stream.
    std::string decode(BitStream& bis, size_t startPos, size_t endPos);
};


#endif // _HUFFMAN_ALGORITHM_HPP_