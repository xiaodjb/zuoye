# Windows (cl) Makefile
CXX = cl
CC = cl

# EHsc : Specifies exception handling model (`extern "C"` functions can throw).Required for C++ exceptions.
CXXFLAGS = /std:c++17 /EHsc /W3

# cl does not fully support C++11
# CXXFLAGS = /std:c++11 /EHsc /W3

# w3: Enables warning level 3 (moderate warnings).
# /TC: Treats all source files as C (not C++).  Forces C compilation (ignores file extensions like `.cpp`). Used for C files only.
# /TC should not be needed here. 
# /W3: Sets the warning level to 3 (moderate warnings).
# /W4: Sets the warning level to 4 (high warnings).	

# CFLAGS could be required here for this program. 
CFLAGS = /TC /W3


# Object files
huffman_algorithm.obj: ../../Algorithms/Huffman/huffman_algorithm.cpp
	$(CXX) $(CXXFLAGS) /c /Fo$@ $<

huffman_tree.obj: ../../Algorithms/Huffman/huffman_tree.cpp
	$(CXX) $(CXXFLAGS) /c /Fo$@ $<

huffman_tests.obj: ../../Algorithms/Huffman/Tests/huffman_tests.cpp
	$(CXX) $(CXXFLAGS) /c /Fo$@ $<

linked_list_and_priority_queue_tests.obj: ../../Core/Linked_list_and_priority_queue/Tests/linked_list_and_priority_queue_tests.cpp
	$(CXX) $(CXXFLAGS) /c /Fo$@ $<

bit_stream.obj: ../../IO/Bit_stream/bit_stream.cpp
	$(CXX) $(CXXFLAGS) /c /Fo$@ $<

bit_stream_tests.obj: ../../IO/Bit_stream/Tests/bit_stream_tests.cpp
	$(CXX) $(CXXFLAGS) /c /Fo$@ $<

c_utils.obj: ../../Utils/C_menu_tools/c_utils.c
	$(CC) $(CFLAGS) /c /Fo$@ $<

test_c_utils.obj: ../../Utils/C_menu_tools/Tests/test_c_utils.cpp
	$(CXX) $(CXXFLAGS) /c /Fo$@ $<

# Targets
all_o: huffman_algorithm.obj huffman_tree.obj huffman_tests.obj linked_list_and_priority_queue_tests.obj bit_stream.obj bit_stream_tests.obj c_utils.obj test_c_utils.obj

huffman_tests.exe: huffman_algorithm.obj huffman_tree.obj huffman_tests.obj bit_stream.obj
	$(CXX) /Fe$@ $^

linked_list_and_priority_queue_tests.exe: linked_list_and_priority_queue_tests.obj
	$(CXX) /Fe$@ $^

bit_stream_tests.exe: bit_stream_tests.obj bit_stream.obj
	$(CXX) /Fe$@ $^

c_utils_tests.exe: c_utils.obj test_c_utils.obj
	$(CXX) /Fe$@ $^

all_exe: huffman_tests.exe linked_list_and_priority_queue_tests.exe bit_stream_tests.exe c_utils_tests.exe

# Clean
clean_o:
	del *.obj

clean_exe:
	del *.exe

clean_all: clean_o clean_exe

# Phony targets
# .PHONY declares targets that **do not represent actual files**. 
#This prevents conflicts if a file named `clean` or `all` exists in the directory.  
.PHONY: all_o all_exe clean_o clean_exe clean_all