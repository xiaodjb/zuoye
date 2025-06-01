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

#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <stdexcept>
#include <iterator>
#include <utility> // For std::forward
#include <iostream> // For std::cout, std::endl
#include <algorithm> // For std::copy_if, std::count_if
#include <vector> // For std::vector

template <typename T>
class DoublyLinkedList {
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        
        explicit Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
        // the above line will have trouble, due to  using unique_ptr
        
        //So, add the following constructor with move semantics also 

        // So Accdept `val` by rvalue reference (move, not copy)
        explicit Node(T&& val) : data(std::move(val)), prev(nullptr), next(nullptr) {}
        // The constructor initializes the data member with the value passed as an argument.


    };

private: 

    /* C++11 allows in-class initialization
    C++14 allows in-class initialization of non-static data members
    C++17 allows in-class initialization of static data members
    C++20 allows in-class initialization of non-static data members with default member initializers
    C++23 allows in-class initialization of non-static data members with default member initializers and constexpr constructors        
    
    The following three lines means that the compiler will initialize the three members before any constructor is called.
    Surely, a constructor can override these values, but if it does not, the default values will be used.
    */
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t len = 0;

    // Helper function to link a new node before or after an existing node
    // "link" can also be understood as "insert".
    // depending on the 'before' parameter
    // If 'before' is true, link before the existing node; otherwise, link after it.
    // If the existing node is null, link at the front or back of the list
    void link_node(Node* new_node, Node* existing_node, bool before) {
        if (!existing_node) { // when existing_node is null or nullptr
            if (!head) {  // when list is empty
                // Initialize head and tail to the new node
                head = tail = new_node;
            } else if (before) {  // when list is not empty and we want to insert at the front
                new_node->next = head;
                head->prev = new_node;
                head = new_node;
            } else { // when list is not empty and we want to insert at the back
                new_node->prev = tail;
                tail->next = new_node;
                tail = new_node;
            }
        } else { // when existing_node is not null or nullptr
            validate_node(existing_node); // Validate the existing node to ensure no obvious errors around it.  
            if (before) { // when we want to insert before the existing node
                // !!!! <Task 15>, provide the missing code !!!!! 
                

            } else { // when we want to insert after the existing node
                new_node->next = existing_node->next;
                new_node->prev = existing_node;
                if (existing_node->next) {
                    existing_node->next->prev = new_node;
                } else {
                    tail = new_node;
                }
                existing_node->next = new_node;
            }
        }
        ++len;
    }

    /* check if the node is in the list. Not a complete check, but a partial one.
    The function checks if the node is null, if it is the head or tail, and if it is linked correctly to its neighbors.
    */
    void validate_node(Node* node) const {
        if (!node) throw std::invalid_argument("Node is null");
        if (node->prev == nullptr && node != head) throw std::invalid_argument("Node is not inthe list:  it has no prev but is not the head");
        if (node->next == nullptr && node != tail) throw std::invalid_argument("Node is not in the list: IT has no next but is not the tail");
        if (node->prev != nullptr && node->next != nullptr) {
            if (node->prev->next != node || node->next->prev != node) {
                throw std::invalid_argument("Node is not in the list: it has neighbors but is not linked correctly with neibhbors");
            }
        } 

        
    }

public:
    // ==================== Core Interface ====================
    DoublyLinkedList() = default; // Default constructor. Explicitly request the default constructor
    // without the = default part, the compiler will not generate a default constructor, because the class has a user-defined constructor.

    
    // Copy constructor for deep copy
    DoublyLinkedList(const DoublyLinkedList& other) : len(other.len) {
        if (other.head) {
            head = new Node(other.head->data);
            Node* current = head;
            Node* other_current = other.head->next;
            while (other_current) {
                current->next = new Node(other_current->data);
                current->next->prev = current;
                current = current->next;
                other_current = other_current->next;
            }
            tail = current;
        }
    }

    // Enable copy assignment operator for deep copy
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear(); // Clear the current list
            if (other.head) {
                head = new Node(other.head->data);
                Node* current = head;
                Node* other_current = other.head->next;
                while (other_current) {
                    current->next = new Node(other_current->data);
                    current->next->prev = current;
                    current = current->next;
                    other_current = other_current->next;
                }
                tail = current;
            }
            len = other.len;
        }
        return *this;
    }

    // Move constructor
    DoublyLinkedList(DoublyLinkedList&& other) noexcept : head(other.head), tail(other.tail), len(other.len) {
        other.head = nullptr;
        other.tail = nullptr;
        other.len = 0;
    }

    // Move assignment operator
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            clear(); // remove all nodes from the current list
            // Transfer ownership of the nodes from other to this
            head = other.head;
            tail = other.tail;
            len = other.len;
            other.head = nullptr;
            other.tail = nullptr;
            other.len = 0;
        }
        return *this;
    }

    // Destructor
    ~DoublyLinkedList() noexcept {
        clear();
    }

    size_t size() const noexcept { return len; }
    bool empty() const noexcept { return len == 0; }

    // Inserting a value at the head (before the head). 
    // to support both copy and move semantics, there are two ways to do it.
    // <Way one>: by writing two functions, one for copy and one for move, as shown below. 

    void insert_front(const T& value) {
        link_node(new Node(value), head, true);
    }

    void insert_front(T&& value) {
        link_node(new Node(std::move(value)), head, true);
    }

    // <Way two>: by writing one function, and using std::forward to handle both copy and move.
    // but doing so, requires the function to be a template function, as shown for the insert_back function below.

    // cannot use T here, because doing so, it will shadow the T of the class, which means inside the function, the type T of the class cannot be used, 
    // so, use U instead of T.
    template<typename U>  
    void insert_back(U&& value) {
         link_node(new Node(std::forward<U>(value)), tail, false);
    }

    /* removing the template line will not work: 
      void insert_back(T&& value) {
         link_node(new Node(std::forward<T>(value)), tail, false);
    }
    because  T&& inside a template class will not work as a universal reference, it will be treated as an rvalue reference. 
    */
    
    // Use <way one> for the insert_before function. 
    // The insert_before function inserts a new node before an existing node.

    // the version with copy semantics
    void insert_before(Node* existing, const T& value) {
        link_node(new Node(value), existing, true);
    }

    // the version with move semantics
    void insert_before(Node* existing, T&& value) {
        // the reason to use std::move is that the value is passed by rvalue reference.
        // but, value inside the function is not a rvalue, it is an lvalue.
        // So, we need to use std::move to convert it to an rvalue.
        link_node(new Node(std::move(value)), existing, true); 
    }

    // The insert_after function inserts a new node after an existing node.
    // <way two> for this function. Make it a template function, and use std::forward to handle both copy and move.

    template<typename U>
    void insert_after(Node* existing, U&& value) {
        link_node(new Node(std::forward<U>(value)), existing, false);
    }

    // the following function is not needed here,
    // because the above function can handle both copy and move.
    // void insert_after(Node* existing, const T& value) {
    //    link_node(new Node(value), existing, false);
    //}

    void remove_front() {
        if (empty()) throw std::out_of_range("List is empty");

        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;

        delete temp;
        --len;
    }

    void remove_back() {
        if (empty()) throw std::out_of_range("List is empty");

        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;

        delete temp;
        --len;
    }

    void remove(Node* node) {
        validate_node(node);

        if (node == head) return remove_front();
        if (node == tail) return remove_back();

        // when the node has both next and prev nodes
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        --len;
    }

    void clear() noexcept {
        while (!empty()) {
            remove_front();
        }
    }

    // ==================== Accessors ====================

    // Accessors for the first and last elements
    // These functions return a reference to the first and last elements in the list.
    // If the list is empty, they throw an out_of_range exception.
    // The const versions return a const reference to the first and last elements.


    T& front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    // ==================== Iterators ====================

    // Bidirectional iterator for the list
    class iterator {
        Node* current;
        DoublyLinkedList<T>* list;  // Added
    public:
        // [knowledge]: in a template class, using is better than typedef. 
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit iterator(Node* node, DoublyLinkedList<T>* lst = nullptr)
            : current(node), list(lst) {}  // Updated

        // [knowledge]: an iterator class should  
        // Provides operator*, prefix operator++, operator==, and operator!=.

        // Dereference operator
        T& operator*() { return current->data; }

        // Arrow operator. It is optional, but it is a good practice to implement it.. 
        T* operator->() { return &current->data; }

        // Prefix increment operator
        iterator& operator++() {
            current = current->next;
            return *this;
        }

        // Postfix increment operator
        // The int parameter is used to distinguish between prefix and postfix increment operators.
        // It is not used in the implementation.
        iterator operator++(int) {
            iterator temp = *this;
            current = current->next;
            return temp;
        }

        // Prefix decrement operator (fixed)
        iterator& operator--() {
            if (current == nullptr) {
                if (list) current = list->tail;  // Handle end() case
            } else {
                current = current->prev;
            }
            return *this;
        }

        // Postfix decrement operator
        iterator operator--(int) {
            iterator temp = *this;
            if (current == nullptr) {
                if (list) current = list->tail;
            } else {
                current = current->prev;
            }
            return temp;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }

        Node* node() { return current; }
    };

    // Const bidirectional iterator for the list
    class const_iterator {
        const Node* current;
        const DoublyLinkedList<T>* list;  // Added
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        explicit const_iterator(const Node* node, const DoublyLinkedList<T>* lst = nullptr)
            : current(node), list(lst) {}  // Updated

        // Dereference operator
        const T& operator*() const { return current->data; }

        // Arrow operator
        const T* operator->() const { return &current->data; }

        // Prefix increment operator
        const_iterator& operator++() {
            current = current->next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator temp = *this;
            current = current->next;
            return temp;
        }

        // Prefix decrement operator (fixed)
        const_iterator& operator--() {
            if (current == nullptr) {
                if (list) current = list->tail;  // Handle end() case
            } else {
                current = current->prev;
            }
            return *this;
        }

        // Postfix decrement operator
        const_iterator operator--(int) {
            const_iterator temp = *this;
            if (current == nullptr) {
                if (list) current = list->tail;
            } else {
                current = current->prev;
            }
            return temp;
        }

        // needed to support range-based for loops of the container
        bool operator==(const const_iterator& other) const {
            return current == other.current;
        }

        // needed to support range-based for loops of the container
        bool operator!=(const const_iterator& other) const {
            return current != other.current;
        }

        const Node* node() const { return current; }
    };

    // Returns an iterator to the beginning of the list
    // needed to support range-based for loops of the container
    // The begin() function returns an iterator pointing to the first element of the list.
    iterator begin() { return iterator(head, this); }

    // Returns an iterator to the end of the list
    // The end iterator points to the position after the last element in the list.
    // needed to support range-based for loops of the container. 
    iterator end() { return iterator(nullptr, this); }

    // Returns a const iterator to the beginning of the list
    const_iterator begin() const { return const_iterator(head, this); }

    // Returns a const iterator to the end of the list
    const_iterator end() const { return const_iterator(nullptr, this); }
};

#endif // DOUBLY_LINKED_LIST_HPP