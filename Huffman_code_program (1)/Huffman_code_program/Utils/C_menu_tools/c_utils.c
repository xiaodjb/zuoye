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
 
#include <stdio.h>
#include "c_only_utils.h"

void clear_input_queue() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

char get_menu_choice(const char* choices) {
    char input;
    do {
        printf("Enter choice [%s]: ", choices);
        input = getchar();
        clear_input_queue();
        
        for(const char* p = choices; *p; p++) {
            if(*p == input) return input;
        }
        printf("Invalid choice!\n");
    } while(1);
}