/*********************************************************** 
 * CS111 OOP 2025 Homework 2 
 * Program designed and implemented by the instructor
 * Zhiyao Liang  ( zyliang@must.edu.mo )                                
 * Date: 2025-May                                       
 ***********************************************************/

// Test both the priority queue based on list and the one based on heap
// This test file is designed to test the functionality of a doubly linked list and a priority queue.
// It includes tests for various operations on the doubly linked list, such as insertion, removal, and iteration.
// It also tests the priority queue's functionality, including enqueueing and dequeueing elements.
// The tests are designed to ensure that the data structures work correctly and efficiently.
// The test results are printed to the console, indicating whether each test passed or failed.
// The test results are summarized at the end, showing the total number of tests, how many passed, and how many failed.
// This test file is designed to be compiled and run as a standalone program.




#include "../doubly_linked_list.hpp"
#include "../priority_queue.hpp"
#include <iostream>
#include <vector>
#include <functional>

#define TEST_FUNCTION(name) \
    bool name() { \
        std::cout << "Testing " << #name << "... "; \
        bool success = true;

#define END_TEST \
        std::cout << (success ? "PASSED" : "FAILED") << std::endl; \
        return success; \
    }

// ==================== Doubly Linked List Tests ====================
TEST_FUNCTION(test_empty_list)
    DoublyLinkedList<int> list;
    success = list.empty() && list.size() == 0;
END_TEST

TEST_FUNCTION(test_list_insert_front_back)
    DoublyLinkedList<int> list;
    list.insert_front(2);
    list.insert_front(1);
    list.insert_back(3);
    
    success = list.size() == 3;
    if (success) {
        auto it = list.begin();
        success = (*it == 1) && (*(++it) == 2) && (*(++it) == 3);
    }
END_TEST

TEST_FUNCTION(test_list_iterators)
    DoublyLinkedList<int> list;
    list.insert_back(1);
    list.insert_back(2);
    list.insert_back(3);
    std::vector<int> forward, reverse;
    std::cout <<"\n" ;
    
    // Forward iteration
    for (auto& item : list) {
        forward.push_back(item);
        std::cout << item << " " << "pushed back" << " forwardly " <<std::endl;
    }
    
    // Reverse iteration
    auto rit = list.end();
    while (rit != list.begin()) {
        --rit;
        reverse.push_back(*rit);
        std::cout << *rit << " " << "pushed back" << " backwardly " <<std::endl;
    }
    
    success = (forward == std::vector<int>{1, 2, 3}) && 
             (reverse == std::vector<int>{3, 2, 1});
END_TEST

TEST_FUNCTION(test_list_remove_operations)
    DoublyLinkedList<int> list;
    list.insert_back(1);
    list.insert_back(2);
    list.insert_back(3);
    list.insert_back(4);
    
    // Remove from middle
    auto it = list.begin();
    ++it; // Points to 2
    list.remove(it.node());
    
    // Remove front
    list.remove_front();
    
    // Remove back
    list.remove_back();
    
    success = list.size() == 1 && *list.begin() == 3;
END_TEST

TEST_FUNCTION(test_list_copy_semantics)
    DoublyLinkedList<int> original;
    original.insert_back(1);
    original.insert_back(2);
    original.insert_back(3);
    DoublyLinkedList<int> copy1(original); // Copy constructor
    DoublyLinkedList<int> copy2;
    copy2 = original; // Copy assignment
    
    original.insert_back(4); // Modify original
    
    success = copy1.size() == 3 && copy2.size() == 3 &&
             *(--copy1.end()) == 3 && *(--copy2.end()) == 3;
END_TEST

TEST_FUNCTION(test_list_move_semantics)
    DoublyLinkedList<int> original;
    original.insert_back(1);
    original.insert_back(2);
    original.insert_back(3);
    DoublyLinkedList<int> moved(std::move(original)); // Move constructor
    
    DoublyLinkedList<int> moved2;
    moved2 = std::move(moved); // Move assignment
    
    success = original.empty() && moved.empty() && 
             moved2.size() == 3 && *moved2.begin() == 1;
END_TEST

// ... [Keep all linked list tests unchanged] ...

// ==================== Priority Queue Tests ====================
TEST_FUNCTION(test_list_min_priority_queue_order)
    // bug fixed 
    // PriorityQueue<int, std::less<int>, OrderedLinkedListContainer> pq;
    
    PriorityQueue<int, std::greater<int>, OrderedLinkedListContainer> pq;
    pq.enqueue(3);
    pq.enqueue(1);
    pq.enqueue(4);
    pq.enqueue(2);
    
    std::vector<int> results;
    while (!pq.empty()) {
        results.push_back(pq.dequeue());
    }
    
    success = results == std::vector<int>{1, 2, 3, 4};
END_TEST

TEST_FUNCTION(test_list_max_priority_queue_order)
    // bug fixed
    // PriorityQueue<int, std::greater<int>, OrderedLinkedListContainer> pq;
    PriorityQueue<int, std::less<int>, OrderedLinkedListContainer> pq;
    pq.enqueue(3);
    pq.enqueue(1);
    pq.enqueue(4);
    pq.enqueue(2);
    
    std::vector<int> results;
    while (!pq.empty()) {
        results.push_back(pq.dequeue());
    }
    
    success = results == std::vector<int>{4, 3, 2, 1};
END_TEST

TEST_FUNCTION(test_list_empty_priority_queue)
    PriorityQueue<int, std::less<int>, OrderedLinkedListContainer> pq;
    bool exception_thrown = false;
    
    try {
        pq.dequeue();
    } catch (const std::out_of_range&) {
        exception_thrown = true;
    }
    
    success = exception_thrown && pq.empty();
END_TEST

TEST_FUNCTION(test_list_priority_queue_move_semantics)
    // bug fixed
    // PriorityQueue<int, std::less<int>, OrderedLinkedListContainer> pq1;

    PriorityQueue<int, std::less<int>, OrderedLinkedListContainer> pq1;
    pq1.enqueue(3);
    pq1.enqueue(1);
    
    PriorityQueue<int, std::less<int>, OrderedLinkedListContainer> pq2(std::move(pq1));
    PriorityQueue<int, std::less<int>, OrderedLinkedListContainer> pq3;
    pq3 = std::move(pq2);
    
    success = pq1.empty() && pq2.empty() && 
             // bug fixed
             // pq3.dequeue() == 1 && pq3.dequeue() == 3;
             pq3.dequeue() == 3 && pq3.dequeue() == 1;
END_TEST

TEST_FUNCTION(test_heap_min_priority_queue_order)
    //PriorityQueue<int, std::less<int>, OrderedLinkedListContainer> pq;
    // PriorityQueue<int, std::less<int>, VectorHeapContainer> pq;
    PriorityQueue<int, std::greater<int>, VectorHeapContainer> pq;
    pq.enqueue(3);
    pq.enqueue(1);
    pq.enqueue(4);
    pq.enqueue(2);
    
    std::vector<int> results;
    while (!pq.empty()) {
        results.push_back(pq.dequeue());
    }
    
    success = results == std::vector<int>{1, 2, 3, 4};
END_TEST

TEST_FUNCTION(test_heap_max_priority_queue_order)
    //PriorityQueue<int, std::greater<int>, OrderedLinkedListContainer> pq;
    PriorityQueue<int, std::less<int>, VectorHeapContainer> pq;
    pq.enqueue(3);
    pq.enqueue(1);
    pq.enqueue(4);
    pq.enqueue(2);
    
    std::vector<int> results;
    while (!pq.empty()) {
        results.push_back(pq.dequeue());
    }
    
    success = results == std::vector<int>{4, 3, 2, 1};
END_TEST



// ==================== Main Test Runner ====================
int main() {
    std::vector<bool> results;
    
    // Linked List Tests
    results.push_back(test_empty_list());
    results.push_back(test_list_insert_front_back());
    results.push_back(test_list_iterators());
    results.push_back(test_list_remove_operations());
    results.push_back(test_list_copy_semantics());
    results.push_back(test_list_move_semantics());
    
    // Priority Queue Tests
    results.push_back(test_list_min_priority_queue_order());
    results.push_back(test_list_max_priority_queue_order());
    results.push_back(test_list_empty_priority_queue());
    results.push_back(test_list_priority_queue_move_semantics());

    results.push_back(test_heap_min_priority_queue_order());
    results.push_back(test_heap_max_priority_queue_order());
    
    // Print summary
    size_t passed = std::count(results.begin(), results.end(), true);
    std::cout << "\nTest Results:\n"
              << "Total: " << results.size() << "\n"
              << "Passed: " << passed << "\n"
              << "Failed: " << results.size() - passed << std::endl;
    
    return (passed == results.size()) ? 0 : 1;
}