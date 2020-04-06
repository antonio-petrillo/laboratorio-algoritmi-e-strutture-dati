#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sl_list.h"

#define randomize srand(time(NULL))
#define random(x) rand()%x

SL_NodePtr sl_union(const SL_NodePtr L1, const SL_NodePtr L2);
void sl_union_rec(const SL_NodePtr L1, const SL_NodePtr L2, SL_NodePtr* L3);

int main(int argc, char** argv){
    randomize;
    SL_NodePtr l1 = makelist_sl();
    SL_NodePtr l2 = makelist_sl();
    for(int i=0; i<10; i++){
        l1 = insert_in_head(l1, random(4));
        l2 = insert_in_head(l2, random(4));
    }
    printf("stampa della lista 1\n");
    print_sl(l1);
    printf("stampa della lista 2\n");
    print_sl(l2);
    printf("stampa della lista unione\n");
    SL_NodePtr l3 = sl_union(l1, l2);
    print_sl(l3);
    return 0;
}

SL_NodePtr sl_union(const SL_NodePtr L1, const SL_NodePtr L2){
    SL_NodePtr Lres = makelist_sl();
    sl_union_rec(L1, L2, &Lres);
    return Lres;
}

void sl_union_rec(const SL_NodePtr L1, const SL_NodePtr L2, SL_NodePtr* L3){
    if(!L1 && L2) sl_union_rec(L1, L2->next, L3);
    else if(L1 && L2) sl_union_rec(L1->next, L2, L3);
    else if(!L1 && !L2) return;
    if(!L1 && L2){
        if(!(*L3)) *L3 = insert_in_head(*L3, L2->value);
        else if(!search(*L3, L2->value)) *L3 = insert_in_head(*L3, L2->value);
    }else if(L1 && L2){
        if(!search(*L3, L1->value)) 
            *L3 = insert_in_head(*L3, L1->value);
    }else if(L1 && !L2){
        *L3 = insert_in_head(*L3, L1->value);
    }
    return;
}