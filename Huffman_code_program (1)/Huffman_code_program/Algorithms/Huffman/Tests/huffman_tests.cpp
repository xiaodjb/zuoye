/*********************************************************** 
 * Program made by the teacher of the course CS111 2025 MUST 
 ***********************************************************/

#include "../huffman_tree.hpp"
#include "../huffman_algorithm.hpp"

#include <climits> // for CHAR_BIT

// Macros for defining test functions
#define TEST_FUNCTION(name) \
    bool name() { \
        std::cout <<"----------------------" << std::endl; \
        std::cout << "Testing " << #name << "... "; \
        bool success = true;

#define END_TEST \
        std::cout << (success ? "PASSED" : "FAILED") << std::endl; \
        return success; \
    } 


// define global variables to avoid repetitive computation
static FrequencyMap freqMap;
static EncodingTable encodingTable;
static BitStream bitStream;
static HuffmanTree tree(freqMap); // The tree should be empty at first

//static HuffmanEncoder encoder(tree); // The encoder should be empty at first
// Do not do this, to avoid a trouble. 

static std::unique_ptr<HuffmanEncoder> encoder;  // A pointer to the encoder
static std::unique_ptr<HuffmanDecoder> decoder;  // A pointer to the decoder

static  std::string text = "hello world";


TEST_FUNCTION(test_string_to_frequence_map)
    //FrequencyMap freq_map;
    //std::string text = "hello world";
    int uniqueChars = string_to_frequence_map(text, freqMap);
    
    // printing the results of frequence map
    // print the number of unique characters
    std::cout << "Number of unique characters: " << uniqueChars << std::endl;  
    std::cout << "Frequency Map:\n";
    for (const auto& pair : freqMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // success = (unique_chars == 10) &&  //bug fixed
    success = (uniqueChars == 8) &&
              (freqMap['h'] == 1) && 
              (freqMap['e'] == 1) && 
              (freqMap['l'] == 3) && 
              (freqMap['o'] == 2) && 
              (freqMap[' '] == 1) && 
              (freqMap['w'] == 1) && 
              (freqMap['r'] == 1) && 
              (freqMap['d'] == 1);

    // Check for a character not in the string 
    success = success && (freqMap.find('x') == freqMap.end());
END_TEST

TEST_FUNCTION(test_huffman_tree)
    //FrequencyMap freq_map;
    //std::string text = "hello world";
    //string_to_frequence_map(text, freqMap);
    
    tree = HuffmanTree(freqMap); // use the implicit copy constructor. 
    
    // Print the Huffman tree
    std::cout << "Huffman Tree:\n";
    //print_huffman_tree(tree.get_root());
    tree.print();
    
    // Check the size of the tree
    success = (tree.get_root() != nullptr);
    
    // Check the frequency of a few characters
    success = success && (tree.get_root()->weight == 11); // Total weight
    success = success && (tree.get_root()->is_leaf() == false); // Root is not a leaf

    // end test
    // Check the frequency of a few characters
    // Check the frequency of a few characters
END_TEST


TEST_FUNCTION(test_huffman_tree_to_encoding_table)
    //FrequencyMap freq_map;
    //std::string text = "hello world";
    //string_to_frequence_map(text, freq_map);
    
    //HuffmanTree tree(freq_map);
    //EncodingTable encoding_table;
    huffman_tree_to_encoding_table(tree, encodingTable);

    std::cout << "\nEncoding Table:\n";
    for (const auto& pair : encodingTable) {
        std::cout << pair.first << ": ";
        for (bool bit : pair.second) {
            std::cout << bit;
        }
        std::cout << std::endl;
    }
    
    /*
    success = (encodingTable.size() == 10) && 
              (encodingTable['h'].size() == 3) && 
              (encodingTable['e'].size() == 4) && 
              (encodingTable['l'].size() == 2) && 
              (encodingTable['o'].size() == 2) && 
              (encodingTable[' '].size() == 5) && 
              (encodingTable['w'].size() == 4) && 
              (encodingTable['r'].size() == 5) && 
              (encodingTable['d'].size() == 5);
    */

    // Check the size of encoding for 'l' is shorter than 'e'   
    success = (encodingTable['l'].size() < encodingTable['e'].size()) && 
              (encodingTable['l'].size() == 2) 
              // not true on mac, the following
              //&& (encodingTable['e'].size() == 4)
              ;


    // Check for a character not in the encoding table
    success = success && (encodingTable.find('x') == encodingTable.end());

    

    // Check for a character with the correct encoding
    /* 
    success = success && (encodingTable['h'] == std::vector<bool>{0, 0, 1}) &&
              (encodingTable['e'] == std::vector<bool>{0, 1, 0, 1}) &&
              (encodingTable['l'] == std::vector<bool>{0, 1, 1}) &&
              (encodingTable['o'] == std::vector<bool>{1, 0}) &&
              (encodingTable[' '] == std::vector<bool>{1, 1, 0, 0}) &&
              (encodingTable['w'] == std::vector<bool>{1, 1, 0, 1}) &&
              (encodingTable['r'] == std::vector<bool>{1, 1, 1, 0}) &&
              (encodingTable['d'] == std::vector<bool>{1, 1, 1, 1});
    // Check for a character not in the encoding table
    success = success && (encodingTable.find('x') == encodingTable.end());
    */
    //End the test  
    
END_TEST

// test the encoder and decoder together
// as long as the encode and decoder are matching, i.e., 
// the string is encoded and then decoded back to the original string, it is a good test.
TEST_FUNCTION(test_huffman_encoder_and_decoder)
    //FrequencyMap freq_map;
    //std::string text = "hello world";
    //string_to_frequence_map(text, freq_map);
    
    //HuffmanTree tree(freq_map);
    //HuffmanEncoder encoder(tree); // use the implicit copy constructor.
    
    // It requires C++14. which is automatically suppoted by G++ with version 6 or later. 
    // So, compile with the following command works:
    //  g++ -c huffman_test.cpp
    // but, comopile with the following line does not work:
    // g++ -std=c++11 -c huffman_test.cpp
    // 
    // encoder = std::make_unique<HuffmanEncoder>(tree); 

    // to compitible with C++11, we need to use the following line:
    encoder = std::unique_ptr<HuffmanEncoder>(new HuffmanEncoder(tree));
     
    
    BitStream bit_stream;
    encoder->encode(bit_stream, text);

    // print the bit stream
    std::cout << "Encoded bits: " << std::endl;
    for (size_t i = 0; i < bit_stream.size(); ++i) {
        std::cout << bit_stream[i];
    }
    std::cout << std::endl;
    
    HuffmanDecoder decoder(tree);
    std::string decoded_text = decoder.decode(bit_stream);
    
    success = (decoded_text == text);
    std::cout << "Decoded text: " << decoded_text << std::endl;
    std::cout << "Original text: " << text << std::endl;
    std::cout << "Decoded text matches original text: " << (success ? "true" : "false") << std::endl;

    // show compression ratio
    //   measured by the number of characters times the number of bits in a character
    //   The number of bits in a character is shown by the symbotlic constant CHAR_BIT, whch can be found in the header file <climits>


    int original_size = text.size() *  CHAR_BIT; // measured by the number of bits
    int compressed_size = bit_stream.size() ; // measured by the number of bits  
    double compression_ratio =  static_cast<double>(original_size) / compressed_size;
    std::cout << "Original size: " << original_size  << std::endl;
    std::cout << "Compressed size: " << compressed_size  << std::endl;
    std::cout << "Compression ratio: " << compression_ratio << std::endl;
  

END_TEST


// Test when the text is a string of a single character
TEST_FUNCTION(test_huffman_encoder_single_character)
    FrequencyMap freq_map2;
    std::string text2 = "aaaaaa";
    string_to_frequence_map(text2, freq_map2);

    //print the frequence map
    std::cout << "Frequency Map:\n";
    for (const auto& pair : freq_map2) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    HuffmanTree tree2(freq_map2);

    // print the Huffman tree
    std::cout << "Huffman Tree:\n";
    //print_huffman_tree(tree2.get_root());
    tree2.print();

    std::cout << "tree is built and printed" << std::endl;

    HuffmanEncoder encoder2(tree2); // use the implicit copy constructor.
    std::cout << "encoder is  built" << std::endl;

    HuffmanDecoder decoder2(tree2);
    std::cout << "decoder is  built" << std::endl;
    
    //encoder = std::make_unique<HuffmanEncoder>(tree); 

    // show the encoding table
    EncodingTable encoding_table2;
    huffman_tree_to_encoding_table(tree2, encoding_table2);
    std::cout << "\nEncoding Table:\n";
    // the number of items in the encoding table is :
    std::cout << "The number of items in the encoding table is: " << encoding_table2.size() << std::endl;
    
    for (const auto& pair : encoding_table2) {
        std::cout << pair.first << ": ";
        for (bool bit : pair.second) {
            std::cout << bit;
        }
        std::cout << std::endl;
    }


    BitStream bit_stream2;

    std::cout<< "Calling the encode function of the Encoder" << std::endl;
    encoder2.encode(bit_stream2, text2);
    
    // std::cout<<"the string is  " << text << std::endl;

    // Print the encoded bits
    std::cout << "Encoded bits: ";
    for (size_t i = 0; i < bit_stream2.size(); ++i) {
        std::cout << bit_stream2[i];
    }
    std::cout << std::endl;
    
    success = (bit_stream2.size() > 0);

    // print the decoded text 
    std::string decoded_text2 = decoder2.decode(bit_stream2);
    std::cout << "Decoded text: " << decoded_text2 << std::endl;

    success = success && (decoded_text2 == text2);
    std::cout << "Original text: " << text2 << std::endl;
    std::cout << "Decoded text matches original text: " << (success ? "true" : "false") << std::endl;

    END_TEST

 
// A Test with a long string
TEST_FUNCTION(test_huffman_encoder_long_string)
    FrequencyMap freq_map3;
    std::string text3 =  
R"(The quick brown fox jumps over the lazy dog. 1234567890
"To be, or not to be: that is the question" - Hamlet
Lorem ipsum dolor sit amet, consectetur adipiscing elit. 
C++ programmers know that Huffman coding achieves optimal prefix coding!
Pack my box with five dozen liquor jugs. 
Bright vixens jump; dozy fowl quack. 
How razorback-jumping frogs can level six piqued gymnasts!
Sphinx of black quartz, judge my vow.
The five boxing wizards jump quickly. 
Jackdaws love my big sphinx of quartz.)";

    // print the original text
    std::cout << "Original text: " << text3 << std::endl;
    // print the size of the text
    std::cout << "Size of the text: " << text3.size() << std::endl;

     string_to_frequence_map(text3, freq_map3);  
    // print the frequency map
    std::cout << "Frequency Map:\n";
    for (const auto& pair : freq_map3) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
   
    
    HuffmanTree tree3(freq_map3);

    // print the Huffman tree
    std::cout << "Huffman Tree:\n";
    //print_huffman_tree(tree3.get_root());
    tree3.print();
    std::cout << "tree is built and printed" << std::endl;


    //print the encoding table
    EncodingTable encoding_table3;
    huffman_tree_to_encoding_table(tree3, encoding_table3);
    std::cout << "\nEncoding Table:\n";
    // the number of items in the encoding table is :
    std::cout << "The number of items in the encoding table is: " << encoding_table3.size() << std::endl;
    // print the encoding table
    for (const auto& pair : encoding_table3) {
        std::cout << pair.first << ": ";
        for (bool bit : pair.second) {
            std::cout << bit;
        }
        std::cout << std::endl;
    }


    //HuffmanEncoder encoder(tree); // use the implicit copy constructor.
    
    HuffmanEncoder encoder3(tree3);  
   
    std::cout << "encoder is  built" << std::endl;
     
    BitStream bit_stream3;
    std::cout<< "Calling the encode function of the Encoder" << std::endl;
    encoder3.encode(bit_stream3, text3);
    // std::cout<<"the string is  " << text << std::endl;
    // Print the encoded bits
    std::cout << "Encoded bits: ";
    for (size_t i = 0; i < bit_stream3.size(); ++i) {
        std::cout << bit_stream3[i];
    }

    HuffmanDecoder decoder3(tree3);
    std::cout << std::endl;
    std::string decoded_text3 = decoder3.decode(bit_stream3);
    std::cout << "Decoded text: " << decoded_text3 << std::endl;
    
    // show compression ratio
    int original_size = text3.size() * CHAR_BIT; // measured by the number of characters times the number of bits of char
    int compressed_size = bit_stream3.size() ; // measured by the number of bits  
    double compression_ratio =  static_cast<double>(original_size) / compressed_size;
    std::cout << "Original size: " << original_size  << std::endl;
    std::cout << "Compressed size: " << compressed_size  << std::endl;
    std::cout << "Compression ratio: " << compression_ratio << std::endl;
  
    
    // Check the size of the bit stream
    success =  (bit_stream3.size() > 0);

    success = success && (decoded_text3 == text3);

END_TEST    


/* 
TEST_FUNCTION(test_huffman_encoder)
    //FrequencyMap freq_map;
    //std::string text = "hello world";
    //string_to_frequence_map(text, freq_map);
    
    //HuffmanTree tree(freq_map);
    // encoder = HuffmanEncoder(tree); // use the implicit copy constructor.

    encoder = std::make_unique<HuffmanEncoder>(tree); 
    
    BitStream bit_stream;
    // encoder.encode(bit_stream, text);


    // call the encode function 
    encoder-> encode(bit_stream, text);
    
    // Check the size of the bit stream
    success = (bit_stream.size() > 0);
    
    // Print the encoded bits
    std::cout << "Encoded bits: ";
    for (size_t i = 0; i < bit_stream.size(); ++i) {
        std::cout << bit_stream[i];
    }
    std::cout << std::endl;
    // Check the size of the bit stream
    success = success && (bit_stream.size() > 0);
    // Check the first few bits
    success = success && (bit_stream[0] == 0) && (bit_stream[1] == 0) && (bit_stream[2] == 1);
    // Check the last few bits

    success = success && (bit_stream[bit_stream.size() - 1] == 1) && 
              (bit_stream[bit_stream.size() - 2] == 1) && 
              (bit_stream[bit_stream.size() - 3] == 1);
 
            
    std::cout << std::endl;
END_TEST
*/ 

/*
TEST_FUNCTION(test_huffman_decoder)
    //FrequencyMap freq_map;
    //std::string text = "hello world";
    //string_to_frequence_map(text, freq_map);
    
    //HuffmanTree tree(freq_map);
    //HuffmanEncoder encoder(tree);
    
    BitStream bit_stream;
    encoder->encode(bit_stream, text);
    
    HuffmanDecoder decoder(tree);
    std::string decoded_text = decoder.decode(bit_stream);
    
    success = (decoded_text == text);
    std::cout << "Decoded text: " << decoded_text << std::endl;
    std::cout << "Original text: " << text << std::endl;
    std::cout << "Decoded text matches original text: " << (success ? "true" : "false") << std::endl;
   
   
END_TEST
*/

// ==================== Main Test Runner ====================
int main() {
    std::vector<bool> results;
    
    // Huffman Algorithm Tests
    // it is important to test the functions in the order of their dependencies.
    results.push_back(test_string_to_frequence_map());
    results.push_back(test_huffman_tree());
    results.push_back(test_huffman_tree_to_encoding_table());
    results.push_back(test_huffman_encoder_and_decoder());
    results.push_back(test_huffman_encoder_single_character());
    results.push_back(test_huffman_encoder_long_string());
    //results.push_back(test_huffman_encoder());
    //results.push_back(test_huffman_decoder());
    
    // Print summary
    size_t passed = std::count(results.begin(), results.end(), true);
    std::cout << "\nTest Results:\n"
              << "Total: " << results.size() << "\n"
              << "Passed: " << passed << "\n"
              << "Failed: " << results.size() - passed << std::endl;
    
    return (passed == results.size()) ? 0 : 1;
}

//   
    