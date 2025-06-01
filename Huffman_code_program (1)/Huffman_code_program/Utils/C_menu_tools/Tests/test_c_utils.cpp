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
 

#include "../cpp_only_utils.hpp"
#include <iostream>  

int main() {
    // Call C functions naturally
    clear_input_queue();
    
    char choice = get_menu_choice("ynq");
    std::cout << "User chose: " << choice << std::endl;
    
    return 0;
}