#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rbtree.h"

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

int max(rbTree tree);

int main(int argc, char** argv){
	rbTree tree = makeRbTree();
	Q q;
	q.head = q.tail = NULL;
	printf("%s\n", "inizio inserimento\n");
	for(int i=0; i<atoi(argv[1]); i++){
		printf("%s%d\n", "inserisco: ", i );
		tree = insertRb(tree, i);
		insert(&q, i);
	}
	printf("%s\n", "\nfine inserimento");
	print(tree);
	printf("%s\n", "ricerca del massimo nell'rb");
	clock_t s_avl = clock();
	int massimo = max(tree);
	clock_t e_avl = clock();
	printf("il massimo del'rb e' : %d\n", massimo);
	printf("%s%lf\n", "costo computazionale: ", ((double)(e_avl - s_avl)/CLOCKS_PER_SEC));
	printf("%s\n", "ricerca del massimo nella lista");
	clock_t s_list = clock();
	int massimo2 = max2(q.head);
	clock_t e_list = clock();
	printf("il massimo della lista e' : %d\n", massimo);
	printf("%s%lf\n", "costo computazionale: ", ((double)(e_list - s_list)/CLOCKS_PER_SEC));
  	printf("\n%s\n", "elimino 42");
  	tree = deleteRbNode(tree, 42);
	tree = deleteRbNode(tree, 69);
	tree = deleteRbNode(tree, 84);
	tree = deleteRbNode(tree, 21);
	tree = deleteRbNode(tree, 17);
  	print(tree);
	tree = dropRb(tree);
	return 0;
}

int max(rbTree tree){
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
