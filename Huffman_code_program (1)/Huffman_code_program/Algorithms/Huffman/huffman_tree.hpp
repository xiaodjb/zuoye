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

#ifndef HUFFMAN_TREE_HPP
#define HUFFMAN_TREE_HPP

/*
- The plan is: 

  ```
                  +-------------+
                  |  Node (ABC) |
                  +------+------+
                         |
          +---------------+---------------+
          |                               |
  +-------+-------+               +-------+-------+
  |  LeafNode     |               | InternalNode |
  | (concrete)    |               | (concrete)   |
  +---------------+               +--------------+
  ```
*/


#include <memory>
#include <unordered_map>
#include "../../Core/Linked_list_and_priority_queue/priority_queue.hpp"




// Abstract Base Class (ABC) for Huffman nodes
class HuffmanNode {
public:
    const int weight;
    virtual ~HuffmanNode() = default;
    HuffmanNode(int w = 0) : weight(w) {} // It is also a default constructor
    virtual bool is_leaf() const = 0; // Pure virtual function
};

// Leaf node (implements ABC)
class LeafNode : public HuffmanNode {
public:
    const char character;
    LeafNode(char c, int w = 1) : HuffmanNode(w), character(c) {}
    bool is_leaf() const override { return true; }
};

// Internal node (uses move semantics for children)
// Only an internal node can have children.
// The left and right children are stored as unique_ptrs to ensure proper memory management.
class InternalNode : public HuffmanNode {
public:
    const std::unique_ptr<HuffmanNode> left;
    const std::unique_ptr<HuffmanNode> right;

    InternalNode(std::unique_ptr<HuffmanNode> l, std::unique_ptr<HuffmanNode> r) 
        : HuffmanNode(l->weight + r->weight), 
          left(std::move(l)), 
          right(std::move(r)) {}  // unique ptrs are moved, not copied

    bool is_leaf() const override { return false; }
};


// Comparator struct for min-heap behavior
// This struct is used to compare two Huffman nodes based on their weights.
// it will be used in a min-priority-queue, like a min-heap. 
// An object of this kind is callable. For example 
// comp(a, b) is true, when a should dequeue after b, and b should dequeue before a.
// This is the opposite of the default behavior of std::less<T>, which can be used in a max-priority-queue. 
struct CompareNodes {
    bool operator()(  
        const std::unique_ptr<HuffmanNode>& a,
        const std::unique_ptr<HuffmanNode>& b
    ) const {
        return a->weight > b->weight;  
        // Min-heap:  need to use the a "greater than" b relation. smaller weight has higher priority to dequeue.
        // This is the opposite of the default behavior of std::less<T>, which can be used in a max-priority-queue.
    }
};

// This function prints the Huffman tree in a human-readable format
// It uses recursion to traverse the tree and print each node's character and weight
// It takes a pointer to the root node and an optional depth parameter for formatting
// The function is defined in the huffman_algorithm.cpp file
// This declaration should appear before the definition of the HuffmanTree class
// because the HuffmanTree class has a print function that calls this function.
void print_huffman_tree(const HuffmanNode* node, int depth = 0, const char* message = "");

// Builds Huffman Tree using the Core priority queue

// One option
// make it a template class, so that the container type can be chosen 
// the type parameter Container has a default a value, so a common user can ignore the technical details of choosing a container

//template <
//    template <typename, typename> class Container = OrderedLinkedListContainer
//>

class HuffmanTree {
    std::unique_ptr<HuffmanNode> root;

public:
    explicit HuffmanTree(const std::unordered_map<char, int>& freq);

    // Function to get the root of the Huffman tree
    // This function returns a pointer to the root node of the Huffman tree.
    // The get function belongs to smart pointers, not to the class.
    // The get function returns a pointer to the managed raw pointer, 
    // which is the pointer to the root node).
    const HuffmanNode* get_root() const { return root.get(); }

    void print() {
        print_huffman_tree(root.get(), 0, "Root: ");
    }
};



#endif