#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H 1

#include "rbtree_library.h"
#include "request.h"

typedef struct library_manager_struct{
    rbtree library;
    char* filename;
    char loan_filename[14];
    char request_filename[18];
    loan_list_t loan_list;
    request_queue_t request_queue;
}* library_manager_t; 

library_manager_t make_library_manager(char* filename);

void load_libray(library_manager_t library_manager);
void load_libray_helper(rbtree library, FILE* fp);
void store_library(library_manager_t library_manager);
void store_library_helper(rb_node node, FILE* fp);
void create_backup(library_manager_t library_manager);
void delete_library(library_manager_t library_manager);
void load_request(library_manager_t library_manager);
void store_request(library_manager_t library_manager);
void load_loan_list(library_manager_t library_manager);
void store_loan_list(library_manager_t library_manager);

#defin STEP_BY_STEP 1;
void handle_library_request(library_manager_t library_manager);


#endif
