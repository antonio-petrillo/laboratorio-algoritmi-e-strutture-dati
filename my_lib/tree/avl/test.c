#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char** argv){
    avlTree tree1 = makeAvlTree();
    avlTree tree2 = makeAvlTree();
    for(int i=0; i<10; i++) tree1 = insertAvl(tree1, i);
    for(int i=9; i<20; i++) tree2 = insertAvl(tree2, i);
    avlTree tree_uni = unionAvlTree(tree1, tree2);
    avlTree tree_int = intersectAvlTree(tree1, tree2);
    avlTree tree_dif = differenceAvlTree(tree1, tree2);
    avlTree tree_copy = copyAvlTree(tree1);
    printf("stampa dell'albero 1:\n");
    inOrderAvlTree(tree1);
    printf("\nstampa dell'albero 2:\n");
    inOrderAvlTree(tree2);
    printf("\nstampa dell'albero uni:\n");
    inOrderAvlTree(tree_uni);
    printf("\nstampa dell'albero int:\n");
    inOrderAvlTree(tree_int);
    printf("\nstampa dell'albero dif:\n");
    inOrderAvlTree(tree_dif);
    printf("\nstampa dell'albero copy:\n");
    inOrderAvlTree(tree_copy);
    printf("\naggiungo un duplicato alla copia e successivamente li rimuovo:\n");
    for(int i=0; i<10; i++) tree_copy = insertAvl(tree_copy, i);
    inOrderAvlTree(tree_copy);
    printf("\nstampa dopo la rimozione dei duplicati\n");
    removeDuplicatesAvlTree(&tree_copy);
    inOrderAvlTree(tree_copy);
}