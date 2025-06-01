/*********************************************************** 
 * CS111 OOP 2025 Homework 2 
 * Program designed and implemented by the instructor
 * Zhiyao Liang  ( zyliang@must.edu.mo )                                
 * Date: 2025-May                                       
 ***********************************************************/

#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <functional>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "doubly_linked_list.hpp"

// ==================== Container Policies ====================
template <typename T, typename Compare>
struct VectorHeapContainer {
    std::vector<T> data;
    Compare comp; // comp(x,y) returns true if x > y logically

    template<typename U>
    void insert(U && value) {

        // the template function can be called with any type U, but U must be convertible to T.
        // Without the assert (as shown below), the code will compile, but it may not work as expected if U is not convertible to T.
        // and the program will not be able to compile if U is not convertible to T, without much information.
        // The static_assert is a compile-time assertion that checks if the condition is true. If the condition is false, it generates a compilation error with the specified message.

        // The following requires C++17 
        // static_assert(std::is_convertible_v<U, T>, "Type U must be convertible to T");


        // The C++11 way of doing the same thing is to use the following assert:
        // `std::decay<U>::type` ensures type comparisons are based on the **underlying type** of `U`, ignoring references, qualifiers, and array/function decay.
        static_assert(
            std::is_convertible<typename std::decay<U>::type, T>::value, // C++11 syntax
            "calling VectorHeapContainer::insert() with data of type U. Type U must be implicitly convertible to T");

        /*push_back is a function typically used in C++ container classes, such as std::vector or std::deque, to insert an element at the end of the container. It provides a strong exception guarantee, ensuring that if an exception is thrown during the operation, the container remains in a valid state.*/
        // The function is used to add a new element to the end of the vector, which may require reallocating memory if the current capacity is exceeded. This operation has an amortized constant time complexity, O(1), but can be O(n) in the worst case when reallocation occurs.
        // The function takes a value of type T (or a reference to it) and moves it into the vector. This is particularly useful for optimizing performance when dealing with large objects, as it avoids unnecessary copying.  
        // The std::forward<U>(value) is a utility function that allows perfect forwarding of the value, preserving its value category (lvalue or rvalue). This is important for maintaining the efficiency of move semantics in C++.
        // In this case, it is used to insert the value into the vector without unnecessary copying.
        // The function is typically used in conjunction with move semantics to efficiently transfer ownership of resources.
        // It is important to note that the function does not check for capacity or size constraints, so it is the caller's responsibility to ensure that the vector can accommodate the new element.

        data.push_back(std::forward<U>(value));

        /*std::make_heap is a C++ Standard Library algorithm that transforms a range of elements into a heap, in this case, a max-heap. It is typically used to prepare a container for heap operations like push_heap and pop_heap.
        */

        /*push_heap is a C++ Standard Library algorithm that adjusts a range of elements to maintain the max-heap property after adding a new element to the end of the range. It is typically used in conjunction with std::make_heap and std::pop_heap for heap operations.
        */

       // The comp function is a comparison function that defines the heap property. In this case, it is used to determine the order of elements in the heap. The function takes two elements as arguments and returns true if the first element should come before the second in the heap.
        // The function takes a range of elements (in this case, the entire vector) and a comparison function (comp) to determine the heap property. It rearranges the elements in the range so that the largest element is at the front of the range, while maintaining the heap property for the remaining elements.
        
        std::push_heap(data.begin(), data.end(), comp);
    }

    T extract() {
        // Check if the heap is empty before attempting to extract an element
        // If the heap is empty, throw an out_of_range exception
        if (data.empty()) throw std::out_of_range("Heap is empty");
        
        // std::pop_heap is a C++ Standard Library algorithm that adjusts a range of elements to maintain the max-heap property after removing the largest element (the root) from the heap. It is typically used in conjunction with std::make_heap and std::push_heap for heap operations.
        // The function takes a range of elements (in this case, the entire vector) and a comparison function (comp) to determine the heap property. It rearranges the elements in the range so that the largest element is moved to the end of the range, while maintaining the heap property for the remaining elements.
        // The function does not actually remove the largest element from the container; it only rearranges the elements. To remove the largest element, you would typically call pop_back() on the vector after calling pop_heap.

        // if we want to pop the smallest element, we need to reverse the comparison. Then, the comparison function will treat the smallest element as the largest.
        // This is done by using std::greater<T>() instead of std::less<T>() as the comparison function.
        std::pop_heap(data.begin(), data.end(), comp); 

        // The last element in the vector is now the largest element, which we will return
        // std::move is a C++ Standard Library function that allows for efficient transfer of resources from one object to another. It is typically used in move semantics to avoid unnecessary copying of objects.
        T value = std::move(data.back());

        // Remove the last element from the vector, which is now the largest element
        // This operation has a constant time complexity, O(1), as it only updates the size of the vector without reallocating memory.
        data.pop_back();        

        // Return the extracted value
        // The function returns the value that was extracted from the heap, which is now stored in the variable value.
        return value;
    }

    size_t size() const noexcept { return data.size(); }
    bool empty() const noexcept { return data.empty(); }
};

template <typename T, typename Compare>
struct OrderedLinkedListContainer {
    DoublyLinkedList<T> list;
    Compare comp; // comp(x,y) returns true if x > y logically

    template<typename U>
    void insert(U&& value) {

        // The static_assert is a compile-time assertion that checks if the condition is true. If the condition is false, it generates a compilation error with the specified message.
        // The following requires C++11
        // static_assert(std::is_convertible_v<U, T>, "Type U must be convertible to T");
        // The C++11 way of doing the same thing is to use the following assert:
        // `std::decay<U>::type` ensures type comparisons are based on the **underlying type** of `U`, ignoring references, qualifiers, and array/function decay.
        static_assert(
            std::is_convertible<typename std::decay<U>::type, T>::value, // C++11 syntax
            "calling OrderedLinkedListContainer::insert() with data of type U. Type U must be implicitly convertible to T");

        // The list is sorted in ascending order, so we need to find the correct position to insert the new value.
        auto it = list.begin();
        
        //move the iterator "it" step by step to the end, until: 
        // when the value is "larger" than the data pointed to by the "It", 
        // or when "it" reaches the end. 
        // !!!! Provide the missing code.  <Task 26> !!!!!!!!!!!!!!!!
       

        
        if (it == list.end()) {
            list.insert_back(std::forward<U>(value));
        } else {
            list.insert_before(it.node(), std::forward<U>(value));
        }
    }

    T extract() {
        T value = std::move(list.begin().node()->data);
        list.remove_front();
        return value;
    }

    size_t size() const noexcept { return list.size(); }
    bool empty() const noexcept { return list.empty(); }
};

// ==================== Priority Queue Class ====================


// The PriorityQueue class is a generic priority queue implementation that uses a container policy to manage its elements.
// It allows for different underlying data structures (like a vector or a linked list) to be used for the priority queue, making it flexible and adaptable to different use cases.
// The class is templated on the type of elements (T), the comparison function (Compare), and the container type (Container).
// The default container is a vector-based heap container, but it can be changed to a linked list-based container if needed.
// The class provides methods for enqueueing and dequeueing elements, as well as checking the size and emptiness of the queue.
// The enqueue method adds an element to the priority queue, while the dequeue method removes and returns the highest-priority element.
// The class uses perfect forwarding to efficiently handle different types of values, including lvalues and rvalues.

/*
*  The line:
*  template <typename, typename> class Container = VectorHeapContainer
*  specifies that the Container template parameter is a template that takes two type parameters and defaults to VectorHeapContainer.
*  This allows the user to specify a different container type when creating an instance of the PriorityQueue class, while still providing a default implementation.
*  The nameless typename is used to indicate that the template parameters are not named in this context, but they are still required for the template instantiation.

*
*  Any class X can work as the Container, as long as
*  - X is a template class with two parametric types
*  - X supports the four functions as used in the PriorityQueue class:
*      - insert()
*      - extract()
*      - empty()
*      - size()
*  
*  Another way is to use independed typename like:
*  template <typename x, typename y> class Container = VectorHeapContainer
*
*  The following way does not work well:
*  template <typename T, typename Compare = std::less<T>, Container = VectorHeapContainer>
*  Because when a template is a parametric type, the parametric types of that template should 
*  1) either be independent to the outside template, 
*  2) or use some independent type name. 
*/
template <
    typename T,
    typename Compare = std::greater<T>, // std::less<T> for max heap
    //template <typename, typename> class Container = VectorHeapContainer
    // Use the VectorHeapContainer for faster performance. 
    template <typename, typename> class Container = OrderedLinkedListContainer
>
class PriorityQueue {
    Container<T, Compare> container;
    Compare comp;

public:
    PriorityQueue() = default;
    explicit PriorityQueue(const Compare& comp) : comp(comp) {}

    template <typename U>
    void enqueue(U&& value) {
        container.insert(std::forward<U>(value));
    }

    T dequeue() {
        if (container.empty()) throw std::out_of_range("Priority queue is empty");
        return container.extract();
    }

    size_t size() const noexcept { return container.size(); }
    bool empty() const noexcept { return container.empty(); }
};

#endif // PRIORITY_QUEUE_HPP