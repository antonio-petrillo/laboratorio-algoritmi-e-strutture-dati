#include <stdio.h>
#include <stdlib.h>
#include "sl_list.h"

SL_NodePtr makelist_sl(){
	return NULL;
}

void sl_error(char* message){
	fprintf(stderr, "%s\n", message);
	exit(1);
}

SL_NodePtr makenode(int value){
	SL_NodePtr newnode = (SL_NodePtr) malloc(sizeof(SL_Node));
	if(!newnode)sl_error("error in function makenode");
	newnode->next = NULL;
	newnode->value = value;
	return newnode;
}

SL_NodePtr insert_in_head(SL_List L, int value){
	SL_NodePtr newnode = makenode(value);
	newnode->next = L;
	return newnode;
}

SL_List insert_in_tail(SL_List L, int value){
	if(!L){
		SL_NodePtr newnode = makenode(value);
		return newnode;
	}else{
		L->next = insert_in_tail(L->next, value);
		return L;
	}
}

SL_List insert_in_order(SL_List L, int value){
	if(!L) return makenode(value);
	else if(L->value < value){
		L->next = insert_in_order(L->next, value);
		return L;
	}else{
		SL_NodePtr newnode = makenode(value);
		newnode->next = L;
		return newnode;
	}
}

SL_List insert_node_in_head(SL_List L, SL_NodePtr node){
	node->next = L;
	return node;
}

SL_List insert_node_in_tail(SL_List L, SL_NodePtr node){
	if(!L) return node;
	L->next = insert_node_in_tail(L->next, node);
	return L;
}

SL_List insert_node_in_order(SL_List L, SL_NodePtr node){
	if(!L) return node;
	else if(L->value < node->value){
		L->next = insert_node_in_order(L->next, node);
		return L;
	}else{
		node->next = L;
		return node;
	}
}

SL_List copy(SL_List L){
	SL_NodePtr L2 = makelist_sl();
	SL_NodePtr iter = L;
	while(iter){
		L2 = insert_in_tail(L2, iter->value);
		iter = iter->next;
	}
	return L2;
}

SL_List order(SL_List L){
	SL_NodePtr L2 = makelist_sl();
	SL_NodePtr tmp;
	int value;
	while(L){
		tmp = L;
		L = L->next;
		L2 = insert_node_in_order(L2, tmp);
	}
	L = drop_sl(L);
	return L2;
}

SL_List remove_duplicates(SL_List L){
	if(L){
		if(search(L->next, L->value)){
			SL_NodePtr tmp = L;
			L = L->next;
			free(tmp);
			L = remove_duplicates(L);
		}else L->next = remove_duplicates(L->next);
	}
	return L;
}

SL_NodePtr remove_with_key(SL_List L, int key){
	if(!L) return NULL;
	if(L->value == key){
		SL_NodePtr tmp = L;
		L = L->next;
		free(L);
	}else L->next = remove_with_key(L->next, key);
	return L;
}

const SL_NodePtr min(const SL_List L){
	if(!L) return NULL;
	else{
		SL_NodePtr tmp = min(L->next);
		if(!tmp) return L;
		else return (tmp->value > L->value) ? L : tmp;
	}
}

const SL_NodePtr  max(const SL_List L){
	if(!L) return NULL;
	else{
		SL_NodePtr tmp = max(L->next);
		if(!tmp) return L;
		else return (tmp->value > L->value) ? tmp : L;
	}
}

unsigned int sl_len(const SL_List L){
	if(!L) return 0;
	return 1 + sl_len(L->next);
}

int is_empty(const SL_List L){
	return (L) ? 1 : 0 ;
}

const SL_NodePtr search(const SL_List L, int value){
	if(!L) return NULL;
	else if(L->value == value) return L;
	else return search(L->next, value);
}

void print_sl(const SL_List L){
	if(!L) return;
	else{
		printf("valore in lista: %d\n", L->value);
		print_sl(L->next);
		return;
	}
}

SL_List drop_sl(SL_List L){
	if(!L) return NULL;
	else{
		/*SL_NOdePtr tmp = L;
		L = L->next;
		free(tmp);
		drop_sl(L);*/
		drop_sl(L->next);
		free(L);
		return NULL;
	}
}

