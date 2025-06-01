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

#include "huffman_algorithm.hpp"

static   bool DEBUG = false; // true;

int string_to_frequence_map(const std::string& text, FrequencyMap& freq_map)
{
    // make sure the frequency map is empty
    freq_map.clear();

    // Iterate through the string and count the frequency of each character
    
    //!!!!!!!!!!! Task 35:  provide the missing code. !!!!!!!!! 
    // For each character in text, increment its entry (its count) in freq_map. 
    

    
    return freq_map.size(); // Return the number of unique characters
}

// a recursive function to build the encoding table. 
// A special case. When this function is called, if prefix be empty, and there is only one node in the tree, 
//  then the encoding of the character is empty. 
// That is a problem. For example, when the string is "AAAAA", and the encoding of the character 'A' is empty,
// there is no way to distinguish between "AAA" and "AAAAA".
// A fix for this is to check if the prefix is empty, and the tree has only one node, set the encoding bit sequence 
// it to {false}, i.e., the encoding of the single character is 0. 

// This is a special case, because the encoding of the character is empty.
// In this case, the encoding table will have only one entry, which is the character itself.

static void build_table(const HuffmanNode *node, BitVector prefix, EncodingTable& encoding_table)
{
    if(node == nullptr)
    {
        //throw std::runtime_error("Node is null");
        //throw std::logic_error("A node is null when it should not be");
        return; //do nothing. 
    }   
    if (node->is_leaf())
    {

        // auto leaf = static_cast<const LeafNode *>(node);
        // In this case static_cast and dynamic_cast are equivalent, because logically it sure that
        // the node is a leaf node; but dynamic_cast is safer. 
        // Comparing static_cast and dynamic_cast, here, the better one is dynamic_cast
        auto leaf = dynamic_cast<const LeafNode *>(node);

        // Check if the prefix is empty and the node is a leaf
        // If the prefix is empty, set it to {false} (0)
        // This is a special case, because the encoding of the character is empty.
        if(prefix.empty() && leaf != nullptr)
        {
            std::cout<< "Encoding of the single character is empty. Set it to {false} (0)" << std::endl;
            prefix.push_back(false); // Set the encoding to {false} (0)
            // bug fixed. should not return here.
            //return; 
        }
    
        encoding_table[leaf->character] = prefix;
        return;
    }
    
    // A more careful way to cast the node to an InternalNode
    auto internal = dynamic_cast<const InternalNode *>(node);
    if(internal == nullptr) {
        //throw std::runtime_error("Node is not an InternalNode");
        throw std::logic_error("A node is not an InternalNode when it should be");
    }
    prefix.push_back(false);
    build_table(internal->left.get(), prefix, encoding_table);

    // without the next line, the prefix will be the same for both left and right children
    // This is because the prefix is passed by value, not by reference.
    // So, we need to remove the last bit which was just added. Bug fixed. 
    prefix.pop_back(); // Remove the last bitwhich was just added
    
    // bug fixed
    // prefix.back() = true;

    prefix.push_back(true);
    
    build_table(internal->right.get(), prefix, encoding_table);
}

void huffman_tree_to_encoding_table(const HuffmanTree& tree, EncodingTable& encoding_table){
    // make sure the encoding table is empty
    encoding_table.clear();

    // Build the encoding table from the Huffman tree
    std::vector<bool> prefix; // it should be empty.

    prefix.clear(); // Clear the prefix vector, so it starts empty. 

    // call the recursive function
    build_table(tree.get_root(), prefix, encoding_table);
}


// constructor for HuffmanEncoder
// It initializes the encoding table by calling the build_table function

// Do not show explict outslide the class
//  error: 'explicit' outside class declaration
// explicit HuffmanEncoder::HuffmanEncoder(const HuffmanTree &t) : tree(t), encoding_table()
HuffmanEncoder::HuffmanEncoder(const HuffmanTree &t) : tree(t), encoding_table()
{
    // make sure the encoding table is empty
    encoding_table.clear();

    //build the encoding table
    huffman_tree_to_encoding_table(tree, encoding_table);
}



void HuffmanEncoder::encode(BitStream &bos, const std::string &text)
{
    // !!!!!!!!!!!!!!!! <Task 38> provide missing code !!!!!!
    /* For each character in text: 
         find its ending, a BitVector which is a vector of bool, from the enclidng_table of the encoder
         Append the bits of the BitVector, one by one, to bos
    */

    
}

HuffmanDecoder::HuffmanDecoder(const HuffmanTree &t) : tree(t) // , current_pos(0)
{
    // No need to build a decoding table, as the tree is already built
}

// The default constructor of HuffmanDecoder is not needed, as we are using a reference to the HuffmanTree

// Destructor is not needed for the HuffmanDecoder, as we are using smart pointers

/* 
HuffmanDecoder ::~HuffmanDecoder()
{
   
}
*/


std::string HuffmanDecoder::decode(BitStream &bis)
{
    // The decode function reads bits from the bit stream and decodes them using the Huffman tree
    // It returns the decoded string

    return decode(bis, 0, bis.size());
}

// The decode function reads bits from the bit stream and decodes them using the Huffman tree
// It returns the decoded string

std::string HuffmanDecoder::decode(BitStream& bis, size_t startPos, size_t endPos)
{
    if(startPos > endPos || startPos >= bis.size() || endPos > bis.size() || startPos < 0 || endPos < 0)
    {
        std::cerr << "Invalid start or end position" << std::endl;
        std::cerr << "start_pos: " << startPos  << " end_pos: " << endPos<< std::endl;
        std::cerr << "bis.size(): " << bis.size() << std::endl;
        throw std::out_of_range("Invalid start or end position");
    }

    std::string result; // it should start as an empty string
    const HuffmanNode *current = tree.get_root();
    // int currentPos = 0; // Reset position

    // size_t currentPos = 0; 

    size_t currentPos = startPos; // Reset position. use size_t for better compatibility with vector indices
    // size_t currentPos = start_pos; // Reset position. use size_t for better compatibility with vector indices
    // Reset position. use size_t for better compatibility with vector indices
    // so, the line: ` while (currentPos < bis.size())` will not produce a warning..

    // !!!!! <Task 39> provide the missing code !!!!!!!!!!!!!!!!!!
    /*
    when currentPos is less than endPos: 
    - if current points to a leaf node
        - get the character at the leaf node, and append it to the string result
        - increment currentPos of reading the BitString bis, 
        - change current, so,  it points to the root node of the true
    - Otherwise, current must point to an internal node. 
        - if the bit at currentPos is 0, change current to its left child. 
        - if the bit at currentPos is 1, change current to its righ child 
        - increment currentPos. 
    
    Hint: when treat "current" as a leaf node or an internal node, should cast it to the corresponding type of node pointer, before using information of the current node
    */

    


    return result;
}

