# Define the compiler and flags
CXX = g++
CC = gcc
CXXFLAGS = -std=c++11 -Wall -Wextra

# ==================== Object File Rules ====================
# Algorithms
huffman_algorithm.o: ../../Algorithms/Huffman/huffman_algorithm.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

huffman_tree.o: ../../Algorithms/Huffman/huffman_tree.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

huffman_tests.o: ../../Algorithms/Huffman/Tests/huffman_tests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Core
linked_list_and_priority_queue_tests.o: ../../Core/Linked_list_and_priority_queue/Tests/linked_list_and_priority_queue_tests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# IO
bit_stream.o: ../../IO/Bit_stream/bit_stream.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bit_stream_tests.o: ../../IO/Bit_stream/Tests/bit_stream_tests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Utils
c_utils.o: ../../Utils/C_menu_tools/c_utils.c
	$(CC) -c $< -o $@

test_c_utils.o: ../../Utils/C_menu_tools/Tests/test_c_utils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==================== Executable Rules ====================
huffman_tests: huffman_algorithm.o huffman_tree.o huffman_tests.o bit_stream.o
	$(CXX) $(CXXFLAGS) -o $@ $^

linked_list_and_priority_queue_tests: linked_list_and_priority_queue_tests.o
	$(CXX) $(CXXFLAGS) -o $@ $^

bit_stream_tests: bit_stream_tests.o bit_stream.o
	$(CXX) $(CXXFLAGS) -o $@ $^

c_utils_tests: c_utils.o test_c_utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# ==================== Meta Targets ====================
.PHONY: all_o all_exe clean_o clean_exe clean_all

all_o: huffman_algorithm.o huffman_tree.o huffman_tests.o \
       linked_list_and_priority_queue_tests.o bit_stream.o \
       bit_stream_tests.o c_utils.o test_c_utils.o

all_exe: huffman_tests linked_list_and_priority_queue_tests \
         bit_stream_tests c_utils_tests

# ==================== Cleanup ====================
clean_o:
	rm -f *.o

clean_exe:
	rm -f huffman_tests linked_list_and_priority_queue_tests bit_stream_tests c_utils_tests

clean_all: clean_o clean_exe