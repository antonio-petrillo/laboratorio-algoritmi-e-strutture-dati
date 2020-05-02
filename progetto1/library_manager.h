#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H 1

#include "rbtree_library.h"

typedef struct library_manager_struct{
    rbtree library;
    char* filename;
}* library_manager_t;


library_manager_t make_library_manager(char* filename);

void load_libray(library_manager_t library_manager);
void load_libray_helper(rbtree library, FILE* fp);
void store_library(library_manager_t library_manager);
void create_backup(library_manager_t library_manager);
void delete_library(library_manager_t library_manager);

#endif