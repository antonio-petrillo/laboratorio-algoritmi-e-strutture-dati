#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"

Btree function(Btree tree);
Btree function_helper(Btree tree, int key);

int main(int argc , char** argv){
	srand(time(NULL));
	Btree tree = makeBtree();
	srand(time(NULL));
	for(int i=0; i<atoi(argv[1]); i++)tree = insertBtree(tree, rand()%100 + 1);
	inOrderBtree(tree);
	printf("\nesecuzione esercizio\n");
	tree = function(tree);
	inOrderBtree(tree);
	tree = dropBtree(tree);
	return 0;
}

Btree function(Btree tree){
		BnodePtr min = minBtree(tree);
		int minVal = min->value;
		tree = function_helper(tree, minVal);
		return tree;
}

Btree function_helper(Btree tree, int key){
	if(tree){
		tree->value -= key;
		tree->left = function_helper(tree->left, key);
		tree->right = function_helper(tree->right, key);
	}
	return tree;
}
