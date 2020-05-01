#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H 1

#include "rbtree_library.h"

typedef struct library_manager_struct{
    rbtree tree;
}* library_manager;


#endif