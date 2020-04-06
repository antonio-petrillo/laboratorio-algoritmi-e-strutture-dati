#include <stdio.h>
#include <stdlib.h>
#include "csl_list.h"

CSL_List incrementa(CSL_List L);

int main(int argc, char** argv){
    CSL_List list = makelist_csl();
    for(int i=0; i<atoi(argv[1]); i++) list = insert_in_head_csl(list, i);
    printf("stampa prima dell'incremento:\n");
    print_csl(list);
    list = incrementa(list);
    printf("\nstampa dopo dell'incremento:\n");
    print_csl(list);
    return 0;
}

CSL_List incrementa(CSL_List L){
    if(!L) return NULL;
    else if(L == L->next){
        L->value *= 2;
    }else if(L->head_of_the_list){
        int add = L->next->value;
        L->next = incrementa(L->next);
         L->value += add;
        return L;
    }else if(L->next->head_of_the_list){
        L->value += L->next->value;
        return L;
    }else{
        L->value += L->next->value;
        L->next = incrementa(L->next);
        return L;
    }
}