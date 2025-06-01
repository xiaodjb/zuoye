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

#ifndef _CPP_ONLY_UTILS_H
#define _CPP_ONLY_UTILS_H

// extern "C" is used to tell the C++ compiler to use C linkage for the functions declared in the header file.
// This is necessary because C++ name mangling is different from C name mangling, and we want to ensure that the C functions can be called from C++ code.

extern "C" {

#include "c_only_utils.h"

// or directly mention the prototype of the functions. 
//void clear_input_queue();
//char get_menu_choice(const char* choices);


}


#endif