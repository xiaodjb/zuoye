

# Define the compiler and the flags
CXX = g++
CXXFLAGS = -std=c++11  

# -------   generate all the .o files --------------
# ======================================================================

#------------- Algorithms .o files

# The following rule works 
huffman_algorithm.o: ../../Algorithms/Huffman/huffman_algorithm.cpp 
	g++  -std=c++11 -c ../../Algorithms/Huffman/huffman_algorithm.cpp 


# using variables, the following rule also works. 
huffman_tree.o: ../../Algorithms/Huffman/huffman_tree.cpp 
	$(CXX) $(CXXFLAGS) -c ../../Algorithms/Huffman/huffman_tree.cpp
	 
# even better, to avoid repeating the path, we can use the following rule
huffman_tests.o: ../../Algorithms/Huffman/Tests/huffman_tests.cpp 
	$(CXX) $(CXXFLAGS) -c  $<
# The $< is a special variable in makefiles that represents the first prerequisite of the rule.
# In this case, it is the first dependency of the rule, which is ../../Algorithms/Huffman/huffman_algorithm.cpp

# --------------- Core .o files 

# we can also use the $@ variable to specify the target of the rule (here is the .o file). Although doing so is not necessary, 
# The $@ is a special variable that represents the target of the rule.
# So, in this case, the rule will compile  ../../Core/Linked_list_and_priority_queue/Tests/linked_list_and_priority_queue.cpp  
# to the target linked_list_and_priority_queue_tests.o
linked_list_and_priority_queue_tests.o: ../../Core/Linked_list_and_priority_queue/Tests/linked_list_and_priority_queue_tests.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@	


# ------------- IO  .o files 

bit_stream.o: ../../IO/Bit_stream/bit_stream.cpp  
	$(CXX) $(CXXFLAGS) -c  $<  

bit_stream_tests.o: ../../IO/Bit_stream/Tests/bit_stream_tests.cpp
	$(CXX) $(CXXFLAGS) -c $<  

# Utils ------------ .o files

# use gcc to compile the c files
c_utils.o: ../../Utils/C_menu_tools/c_utils.c
	gcc  -c $<
	 
test_c_utils.o: ../../Utils/C_menu_tools/Tests/test_c_utils.cpp 
	g++  -c $<

# all the .o files
all_o: huffman_algorithm.o huffman_tree.o huffman_tests.o linked_list_and_priority_queue_tests.o bit_stream.o bit_stream_tests.o c_utils.o test_c_utils.o

# remove the .o files on windows
clean_o:
	del *.o


# ======================================================================
# -------   generate the executable file --------------


# The $^ is a special variable in makefiles that represents all the prerequisites of the rule.
# Otherwise, without using $^, we would have to write all the .o files manually, but this demands more work. 
# Here -o is needed, because otherwise, the default output file will be a.exe 
huffman_tests.exe:  huffman_algorithm.o huffman_tree.o huffman_tests.o bit_stream.o  
	$(CXX) $(CXXFLAGS) -o $@ $^

linked_list_and_priority_queue_tests.exe: linked_list_and_priority_queue_tests.o   
	$(CXX) $(CXXFLAGS) -o $@ $^

bit_stream_tests.exe: bit_stream_tests.o  bit_stream.o
	$(CXX) $(CXXFLAGS) -o $@ $^ 

c_utils_tests.exe: c_utils.o test_c_utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# all the executables
all_exe: huffman_tests.exe linked_list_and_priority_queue_tests.exe bit_stream_tests.exe c_utils_tests.exe

# remove the executables on windows
clean_exe:
	del *.exe

# remove all the .o files and the executables
clean_all:
	del *.o
	del *.exe
