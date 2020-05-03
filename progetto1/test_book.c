#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "rbtree_library.h"
#include "library_manager.h"

int main(int argc, char** argv){
    library_manager_t lb = make_library_manager(argv[1]);
    load_libray(lb);
    in_order_visit_rb(lb->library);
    FILE* fp = fopen("test.txt", "w");
    store_library_helper(lb->library->root, fp);
    fclose(fp);
    return 0;
}
