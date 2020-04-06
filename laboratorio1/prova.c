#include <stdio.h>
#include <stdlib.h>
#include "sl_list.h"

int main(int argc, char** argv){
    SL_List l = makelist_sl();
    for(int i=0; i<5; i++){
        l = insert_in_order(l, i);
        l = insert_in_order(l, i);
    }
    printf("stampa con i duplicati\n");
    print_sl(l);
    printf("stampa dopo la rimozione dei duplicati\n");
    l = remove_duplicates(l);
    print_sl(l);
    l = drop_sl(l);
    return 0;
}