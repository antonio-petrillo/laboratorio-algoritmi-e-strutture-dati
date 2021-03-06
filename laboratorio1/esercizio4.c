#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sl_list.h"

#define randomize srand(time(NULL))
#define random(x) rand()%x

SL_NodePtr sl_difference(const SL_NodePtr L1, const SL_NodePtr L2);
void sl_difference_rec(const SL_NodePtr L1, const SL_NodePtr L2, SL_NodePtr* L3);

int main(int argc, char** argv){
    randomize;
    SL_NodePtr l1 = makelist_sl();
    SL_NodePtr l2 = makelist_sl();
    for(int i=0; i<10; i++){
        l1 = insert_in_head(l1, i);
        l2 = insert_in_head(l2, random(4));
    }
    printf("stampa della lista 1\n");
    print_sl(l1);
    printf("stampa della lista 2\n");
    print_sl(l2);
    printf("stampa della lista sottrazione\n");
    SL_NodePtr l3 = sl_difference(l1, l2);
    puts("\n\n\n");
    print_sl(l3);
    return 0;
}



SL_NodePtr sl_difference(const SL_NodePtr L1, const SL_NodePtr L2){
    SL_NodePtr Lres = makelist_sl();
    sl_difference_rec(L1, L2, &Lres);
    return Lres;
}

void sl_difference_rec(const SL_NodePtr L1, const SL_NodePtr L2, SL_NodePtr* L3){
    if(!L1) return;
    if(!search(L2, L1->value)){
        if(!(*L3)) *L3 = insert_in_head(*L3, L1->value);
        else if(!search(*L3, L1->value)) *L3 = insert_in_head(*L3, L1->value);
    }
    sl_difference_rec(L1->next, L2, L3);
    return;
}
