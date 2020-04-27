#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

Btree esercizio1(Btree tree, int key);
Btree esercizio1Helper(Btree tree);

int main(int argc, char** argv){
    Btree tree = makeBtree();
    int value[11] = {10, 4, 17, 0, 3, 2, 14, 20, 12, 16, 24}; 
    for(int i=0; i<11; i++) tree = insertBtree(tree, value[i]);
    printf("stampa prima della rimozione: \n");
    inOrderBtree(tree);
    tree = esercizio1(tree, 4);
    printf("\nstampa dopo della rimozione: \n");
    inOrderBtree(tree);
    tree = dropBtree(tree);
    return 0;
}

Btree esercizio1(Btree tree, int key){
    if(tree){
        if(tree->value % key == 0 && tree->value != key){
            tree = esercizio1Helper(tree);
        }
        if(tree){
            tree->left = esercizio1(tree->left, key);
            tree->right = esercizio1(tree->right, key);
        }
    }
    return tree;
}

Btree esercizio1Helper(Btree tree){
    if(!tree->left) tree = removeBnode(tree, tree->value);
    else tree->left = esercizio1Helper(tree->left);
    return tree;
}