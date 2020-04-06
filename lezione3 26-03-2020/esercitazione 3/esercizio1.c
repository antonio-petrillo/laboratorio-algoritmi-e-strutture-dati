#include <stdio.h>
#include <stdlib.h>
#include "sl_list.h"

int sum(const SL_NodePtr L);

int main(int argc, char** argv){
    SL_NodePtr List = makelist_sl();
    for(int i=1; i<=100; i++) List = insert_in_head(List, i);
    int somma = sum(List);
    printf("la somma dei valori della lista e': %d\n", somma);
    List = drop_sl(List);
    return 0;
}

int sum(const SL_NodePtr L){
    if(!L) return 0;
    return L->value + sum(L->next);
}