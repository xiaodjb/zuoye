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

// On MacOS, using \ , the path is not recognized
// #include "..\bit_stream.hpp"

#include "../bit_stream.hpp"
#include <iostream>
#include <cstdio>

// ==================== Test Helpers ====================
bool test_append_and_access() {
    BitStream bs;
    bool success = true;

    // Test basic append
    bs.append(1);
    bs.append(0);
    bs.append(true);
    bs.append(false);

    if (bs.size() != 4) {
        std::cerr << "Error: Incorrect size after appending\n";
        success = false;
    }

    // Test bit values
    if (bs[0] != true || bs[1] != false || bs[2] != true || bs[3] != false) {
        std::cerr << "Error: Bit values mismatch\n";
        success = false;
    }

    // Test mutation
    bs[1] = 1;
    if (bs[1] != true) {
        std::cerr << "Error: Bit mutation failed\n";
        success = false;
    }

    return success;
}

bool test_file_operations() {
    const std::string test_file = "bit_stream_test.bin";
    bool success = true;

    try {
        // Write test (3 bits)
        BitStream write_bs;
        write_bs.append(1);
        write_bs.append(0);
        write_bs.append(1);
        write_bs.write_to_file(test_file);

        // Read test
        BitStream read_bs;
        read_bs.read_from_file(test_file);

        if (read_bs.size() != 3) {  // Now will be correct
            std::cerr << "Error: File read size mismatch\n";
            std::cerr << "Expected: 3, Got: " << read_bs.size() << "\n";
            success = false;
        }
    }
    catch (...) {
        success = false;
    }
    
    return success;
}



bool test_error_handling() {
    BitStream bs;
    bool success = true;

    try {
        bs[0];  // Should throw
        std::cerr << "Error: No exception on empty access\n";
        success = false;
    }
    catch (const std::out_of_range&) {}  // Expected
    catch (...) {
        std::cerr << "Error: Wrong exception type\n";
        success = false;
    }

    return success;
}

// ==================== Main Test Runner ====================
int main() {
    int failures = 0;
    const int total_tests = 3;

    std::cout << "Running BitStream module tests...\n\n";

    failures += !test_append_and_access();
    failures += !test_file_operations();
    failures += !test_error_handling();

    std::cout << "\nTest results:\n"
              << "Passed: " << (total_tests - failures) << "\n"
              << "Failed: " << failures << "\n";

    return failures ? 1 : 0;
}
