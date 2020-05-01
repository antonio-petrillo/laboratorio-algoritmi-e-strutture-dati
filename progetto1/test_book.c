#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "rbtree_library.h"

int main(int argc, char** argv){
    fprintf(stdout, "test");
    rbtree library = make_rbtree();
    printf("test");
    FILE* fp = fopen(argv[1], "r");
    printf("test");
    load_library(library, fp);
    printf("end load\n");
    fclose(fp);
    in_order_visit_rb(library);
    fp = fopen(argv[1], "w+");
    store_library(library, fp);
    fclose(fp);
    drop_rbtree(library);
    return 0;
}