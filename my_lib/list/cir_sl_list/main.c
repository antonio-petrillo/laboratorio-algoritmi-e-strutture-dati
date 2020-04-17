#include <stdio.h>
#include <stdlib.h>
#include "csl_list.h"

int main(int argc, char** argv){
    CSL_List l = makelist_csl();
    for(int i=0; i<atoi(argv[1]); i++) l = insert_node_in_order_csl(l, makenode_csl(i));
    multi_print_csl(l, 4);
    // printf("valore della lista: %d\n", l->value);
    // printf("valore della lista: %d\n", l->next->value);
    // printf("valore della lista: %d\n", l->next->next->value);
    // printf("valore della lista: %d\n", l->next->next->next->value);
    l = drop_csl(l);
    return 0;
}
