#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"



Btree removeOdd(Btree tree);
Btree removeEven(Btree tree);
Btree esercizio2(Btree* tree1, Btree* tree2);

int main(int argc, char** argv){
    srand(time(NULL));
    Btree tree1 = makeBtree();
    Btree tree2 = makeBtree();
    Btree treeResult;
    int range = atoi(argv[2]);
    for(int i=0; i<atoi(argv[1]); i++){
        tree1 = insertBtree(tree1, rand()%range );
        tree2 = insertBtree(tree2, rand()%range );
    }
    printf("stampa del primo albero:\n");
    inOrderBtree(tree1);
    printf("\nstampa del secondo albero:\n");
    inOrderBtree(tree2);
    treeResult = esercizio2(&tree1, &tree2);
    printf("\nstampa del primo albero dopo la rimozione dei pari:\n");
    inOrderBtree(tree1);
    printf("\nstampa del secondo albero dopo la rimozione dei dispari:\n");
    inOrderBtree(tree2);
    printf("\nstampa dell'albero risulato:\n");
    inOrderBtree(treeResult);
    tree1 = dropBtree(tree1);
    tree2 = dropBtree(tree2);
    treeResult = dropBtree(treeResult);
    return 0;
}

Btree removeOdd(Btree tree){
    if(tree){
        tree->left = removeOdd(tree->left);
        tree->right = removeOdd(tree->right);
        if(tree->value % 2) tree = removeBnode(tree, tree->value);
    }
    return tree;
}

Btree removeEven(Btree tree){
    if(tree){
        tree->left = removeEven(tree->left);
        tree->right = removeEven(tree->right);
        if(tree->value % 2 == 0) tree = removeBnode(tree, tree->value);
    }
    return tree;
}

Btree esercizio2(Btree* tree1, Btree* tree2){
    *tree1 = removeEven(*tree1);
    *tree2 = removeOdd(*tree2);
    Btree tree3 = unionBtree(*tree1, *tree2);
    return tree3;
}