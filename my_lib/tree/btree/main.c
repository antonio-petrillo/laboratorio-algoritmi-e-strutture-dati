#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"

int main(int argc , char** argv){
	srand(time(NULL));
	Btree tree = makeBtree();
	//for(int i=0; i<atoi(argv[1]); i++) tree = insertBtree(tree, rand()%3000);
	tree = insertBtree(tree, 42);
	tree = insertBtree(tree, 133);
	tree = insertBtree(tree, 2880);
	tree = insertBtree(tree, 84);
	tree = insertBtree(tree, 21);
	inOrderBtree(tree);
	// printf("\nrimuovo 42, 133, 2880, 84, 21\nstampa dopo la rimozione\n\n");
	// tree = removeBnode(tree, 42);
	// tree = removeBnode(tree, 133);
	// tree = removeBnode(tree, 2880);
	// tree = removeBnode(tree, 84);
	// tree = removeBnode(tree, 21);
	// inOrderBtree(tree);
	BnodePtr node = predeccessorBtree(tree, 42);
	printf("il predecessore di 42 e' %d\n", node->value);
	node = predeccessorBtree(tree, 30);
	printf("il predecessore di 30 e' %d\n", node->value);
	node = successorBtree(tree, 84);
	printf("il successore di 42 e' %d\n", node->value);
	node = successorBtree(tree, 135);
	printf("il successore di 135 e' %d\n", node->value);
	tree = dropBtree(tree);
	return 0;
}
