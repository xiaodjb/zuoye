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

#include "huffman_tree.hpp"
#include <iostream>

void print_huffman_tree(const HuffmanNode *node, int depth, const char * message)
{
    if (node == nullptr)
        return;

    // Print the current node
    
    if (node->is_leaf())
    {
        for (int i = 0; i < depth; ++i)
            std::cout << "  ";
        const LeafNode *leaf = static_cast<const LeafNode *>(node);
        std::cout << message << "Leaf: " << leaf->character << " (" << leaf->weight << ")\n";
    }
    else // print the tree in a symmetric way, more interesting. 
    {   
        // !!!!!! Task 34, provide the missing code !!!!!
        /*
        - Cast node to a const pointer to Internal Node   
        - A recursive call to print the left subtree, with an incremented depth, and "[left]" as the message. 
        - print the internal node as follows
            - Ident (print a sequence of "depth" space characters)
            - Print the information of the internal node, including the message, and the weight
            - Print a newline. 
        - A recursive call to print the right subtree, with an incremented depth, and "[left]" as the message. 
        */

        
    }   


}

//  error: 'explicit' outside class declaration
//explicit HuffmanTree::HuffmanTree(const std::unordered_map<char, int> &freq)

//template <template <typename, typename> class Container>
// HuffmanTree<Container>::HuffmanTree(const std::unordered_map<char, int> &freq)
HuffmanTree::HuffmanTree(const std::unordered_map<char, int> &freq)
{
    // Check if the frequency map is empty
    if (freq.empty())
    {
        // throw std::invalid_argument("Frequency map is empty");
        std::cout<< "Frequency map is empty when constructing a Huffman tree" << std::endl;
        root = nullptr; // Set root to nullptr
        return;
        //throw std::invalid_argument("Frequency map is empty");
    }


    // Initialize priority queue with correct comparator
    // PriorityQueue<std::unique_ptr<HuffmanNode>, CompareNodes, Container> pq;
    PriorityQueue<std::unique_ptr<HuffmanNode>, CompareNodes> pq;

    // Add nodes to the queue (assuming method is `insert()`)
    /*
    warning: structured bindings only available with '-std=c++17' or '-std=gnu++17'
85 |         for (const auto& [ch, count] : freq) {
    */



    // !!!!!!!!!! <Task 36.a> , provide the missing code !!!
    /* For each entry (a pair) in freq, which is a the frequency map
       - create a leaf node with the character and count in the pair
       - put the unique pointer of HuffmanNode to this leaf node into the priority queue pq,
          by calling the enqueue function of pq. 
     */ 

   


    if (pq.size() == 0)
    {
        throw std::invalid_argument("Frequency map is empty");
    }


    // Handle the case where there are multiple nodes
    // Combine nodes until only one node remains in the queue
    // Extract nodes (assuming method logic is like `extract_min()`)
    
    // !!!!!!!!!! <Task 36.b> , provide the missing code !!!
    /*  While `pq` has more than 1 elements, 
       take out (dequeue) two elements and create a new Internal Node 
     whose two child are the two elements dequeued 
     (Hint, use std::move() to record the two elements), 
     and enqueue a unique pointer to this node into pq. 
    */
    
    

     if (pq.size() == 1) // Check if there's only one node left. Should be the case.
    {
        root = pq.dequeue(); // Directly assign the single node to root
  
        return;
    }
    else{
        // Handle the case where no nodes are left
        throw std::runtime_error("No nodes left in the priority queue");
    }

    // root = pq.dequeue();
}
