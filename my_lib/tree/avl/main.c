#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

typedef struct list{
	struct list* next;
	int value;
}List;

typedef List* L;

typedef struct{
	L head;
	L tail;
}Q;

void insert (Q* q, int value);
L makenode(int value);
int max2(L l);

int max(avlTree tree);

int main(int argc, char** argv){
	avlTree tree = makeAvlTree();
	Q q;
	q.head = q.tail = NULL;
	printf("%s\n", "inizio inserimento\n");
	for(int i=0; i<atoi(argv[1]); i++){
		printf("%s%d\n", "inserisco: ", i );
		tree = insertAvl(tree, i);
		insert(&q, i);
	}
	tree = insertAvl(tree, 42);
	printf("%s\n", "\nfine inserimento");
	print(tree);
	printf("%s\n", "ricerca del massimo nell'avl");
	clock_t s_avl = clock();
	int massimo = max(tree);
	clock_t e_avl = clock();
	printf("il massimo del'avl e' : %d\n", massimo);
	printf("%s%lf\n", "costo computazionale: ", ((double)(e_avl - s_avl)/CLOCKS_PER_SEC));
	printf("%s\n", "ricerca del massimo nella lista");
	clock_t s_list = clock();
	int massimo2 = max2(q.head);
	clock_t e_list = clock();
	printf("il massimo della lista e' : %d\n", massimo2);
	printf("%s%lf\n", "costo computazionale: ", ((double)(e_list - s_list)/CLOCKS_PER_SEC));
	printf("%s\n", "elimino 42");
	tree = deleteAvlNode(tree, 42);
	tree = deleteAvlNode(tree, 21);
	tree = deleteAvlNode(tree, 1);
	tree = deleteAvlNode(tree, 17);
	tree = deleteAvlNode(tree, 7);
	tree = deleteAvlNode(tree, 31);
	tree = deleteAvlNode(tree, 19);
	tree = deleteAvlNode(tree, 20);
	print(tree);
	tree = dropAvl(tree);
	return 0;
}

int max(avlTree tree){
	if(tree->right) return max(tree->right);
	return tree->value;
}

void insert (Q* q, int value){
	if(!q->head) q->head = q->tail = makenode(value);
	else{
		L newnode = makenode(value);
		q->tail->next = newnode;
		q->tail = newnode;
	}
}

L makenode(int value){
	L newnode = (L)malloc(sizeof(L));
	newnode->next = NULL;
	newnode->value = value;
	return newnode;
}

int max2(L l){
	if(l->next) return max2(l->next);
	return l->value;
}
