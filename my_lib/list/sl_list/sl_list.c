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

SL_NodePtr makenode_sl(int value){
	SL_NodePtr newnode = (SL_NodePtr) malloc(sizeof(SL_Node));
	if(!newnode)sl_error("error in function makenode");
	newnode->next = NULL;
	newnode->value = value;
	return newnode;
}

SL_NodePtr insert_in_head_sl(SL_List L, int value){
	SL_NodePtr newnode = makenode_sl(value);
	newnode->next = L;
	return newnode;
}

SL_List insert_in_tail_sl(SL_List L, int value){
	if(!L){
		SL_NodePtr newnode = makenode_sl(value);
		return newnode;
	}else{
		L->next = insert_in_tail_sl(L->next, value);
		return L;
	}
}

SL_List insert_in_order_sl(SL_List L, int value){
	if(!L) return makenode_sl(value);
	else if(L->value < value){
		L->next = insert_in_order_sl(L->next, value);
		return L;
	}else{
		SL_NodePtr newnode = makenode_sl(value);
		newnode->next = L;
		return newnode;
	}
}

SL_List insert_node_in_head_sl(SL_List L, SL_NodePtr node){
	node->next = L;
	return node;
}

SL_List insert_node_in_tail_sl(SL_List L, SL_NodePtr node){
	if(!L) return node;
	L->next = insert_node_in_tail_sl(L->next, node);
	return L;
}

SL_List insert_node_in_order_sl(SL_List L, SL_NodePtr node){
	if(!L) return node;
	else if(L->value < node->value){
		L->next = insert_node_in_order_sl(L->next, node);
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
		L2 = insert_in_tail_sl(L2, iter->value);
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
		L2 = insert_node_in_order_sl(L2, tmp);
	}
	L = drop_sl(L);
	return L2;
}

SL_List remove_duplicates_sl(SL_List L){
	if(L){
		if(search_sl(L->next, L->value)){
			SL_NodePtr tmp = L;
			L = L->next;
			free(tmp);
			L = remove_duplicates_sl(L);
		}else L->next = remove_duplicates_sl(L->next);
	}
	return L;
}

void remove_with_key_sl(SL_List* L, int key){
	if(!(*L)) return;
	if((*L)->value == key){
		SL_NodePtr tmp = *L;
		*L = (*L)->next;
		free(tmp);
	}else remove_with_key_sl(&(*L)->next, key);
	return ;
}

const SL_NodePtr min_sl(const SL_List L){
	if(!L) return NULL;
	else{
		SL_NodePtr tmp = min_sl(L->next);
		if(!tmp) return L;
		else return (tmp->value > L->value) ? L : tmp;
	}
}

const SL_NodePtr  max_sl(const SL_List L){
	if(!L) return NULL;
	else{
		SL_NodePtr tmp = max_sl(L->next);
		if(!tmp) return L;
		else return (tmp->value > L->value) ? tmp : L;
	}
}

unsigned int sl_len(const SL_List L){
	if(!L) return 0;
	return 1 + sl_len(L->next);
}

int is_empty_sl(const SL_List L){
	return (L) ? 1 : 0 ;
}

const SL_NodePtr search_sl(const SL_List L, int value){
	if(!L) return NULL;
	else if(L->value == value) return L;
	else return search_sl(L->next, value);
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

SL_NodePtr sl_union(const SL_NodePtr L1, const SL_NodePtr L2){
    SL_NodePtr Lres = makelist_sl();
    sl_union_rec(L1, L2, &Lres);
    return Lres;
}

void sl_union_rec(const SL_NodePtr L1, const SL_NodePtr L2, SL_NodePtr* L3){
    if(!L1 && L2) sl_union_rec(L1, L2->next, L3);
    else if(L1 && L2) sl_union_rec(L1->next, L2, L3);
    else if(!L1 && !L2) return;
    if(!L1 && L2){
        if(!(*L3)) *L3 = insert_in_head_sl(*L3, L2->value);
        else if(!search_sl(*L3, L2->value)) *L3 = insert_in_head_sl(*L3, L2->value);
    }else if(L1 && L2){
        if(!search_sl(*L3, L1->value)) 
            *L3 = insert_in_head_sl(*L3, L1->value);
    }else if(L1 && !L2){
        *L3 = insert_in_head_sl(*L3, L1->value);
    }
    return;
}

SL_NodePtr sl_intersect(const SL_NodePtr L1, const SL_NodePtr L2){
    SL_NodePtr Lres = makelist_sl();
    sl_intersect_rec(L1, L2, &Lres);
    return Lres;
}

void sl_intersect_rec(const SL_NodePtr L1, const SL_NodePtr L2, SL_NodePtr* L3){
    if(L1){
        if(search_sl(L2, L1->value)){
            if(!(*L3)) *L3 = insert_in_head_sl(*L3, L1->value);
            if(!search_sl(*L3, L1->value)) *L3 = insert_in_head_sl(*L3, L1->value);
        } 
        sl_intersect_rec(L1->next, L2, L3);
    }else return;
}

SL_NodePtr sl_difference(const SL_NodePtr L1, const SL_NodePtr L2){
    SL_NodePtr Lres = makelist_sl();
    sl_difference_rec(L1, L2, &Lres);
    return Lres;
}

void sl_difference_rec(const SL_NodePtr L1, const SL_NodePtr L2, SL_NodePtr* L3){
    if(!L1) return;
    if(!search_sl(L2, L1->value)){
        if(!(*L3)) *L3 = insert_in_head_sl(*L3, L1->value);
        else if(!search_sl(*L3, L1->value)) *L3 = insert_in_head_sl(*L3, L1->value);
    }
    sl_difference_rec(L1->next, L2, L3);
    return;
}
