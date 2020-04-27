#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"
#include "sl_list.h"

SL_List esercizio4(Btree tree, int key);
Btree esercizio4Helper(Btree tree, int key, SL_List* list);
void inserisciInLista(Btree tree, SL_List* list);

int main(int argc, char** argv){
    srand(time(NULL));
    Btree tree = makeBtree();
    int range = atoi(argv[1]);
    for(int i=0; i<atoi(argv[1]); i++) tree = insertBtree(tree, rand()%range);
    printf("stampa dell'albero prima della rimozione:\n");
    inOrderBtree(tree);
    SL_List list = esercizio4(tree, rand()%range);
    printf("\nstampa dell'albero dopo la rimozione:\n");
    inOrderBtree(tree);
    printf("nodi rimossi:\n");
    print_sl(list);
    tree = dropBtree(tree);
    return 0;
}

SL_List esercizio4(Btree tree, int key){
    SL_List list = makelist_sl();
    tree = esercizio4Helper(tree, key, &list);
    return list;
}

Btree esercizio4Helper(Btree tree, int key, SL_List* list){
    if(tree){
        if(tree->value > key){
            tree->left = esercizio4Helper(tree->left, key, list);
        }else if(tree->value < key){
            tree->right = esercizio4Helper(tree->right, key, list);
        }else{
            inserisciInLista(tree, list);
            tree = dropBtree(tree);
            puts("");
        }
    }
    return tree;
}

void inserisciInLista(Btree tree, SL_List* list){
    if(tree){
        *list = insert_in_order_sl(*list, tree->value);
        inserisciInLista(tree->left, list);
        inserisciInLista(tree->right, list);
    }
    return;
}