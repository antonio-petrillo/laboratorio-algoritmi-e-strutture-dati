#include <stdio.h>
#include <stdlib.h>
#include "dl_list.h"

void dl_error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

DL_List makelist_dl(){
    return NULL;
}

DL_NodePtr makenode_dl(int value){
    DL_NodePtr newnode = (DL_NodePtr) malloc(sizeof(DL_Node));
    if(!newnode) dl_error("error in function makenode_dl");
    newnode->next = newnode->prev = NULL;
    newnode->value = value;
    return newnode;
}

DL_List insert_in_head_dl(DL_List L, int value){
    DL_NodePtr newnode = makenode_dl(value);
    newnode->next = L;
    if(L) L->prev = newnode;
    return newnode;
}

DL_List insert_in_tail_dl(DL_List L, int value){
    if(!L) return makenode_dl(value);
    L->next = insert_in_tail_dl(L->next, value);
    L->next->prev = L;
    return L;
}

DL_List insert_in_order_dl(DL_List L, int value){
    if(!L) return makenode_dl(value);
    if(value > L->value){
        L->next = insert_in_order_dl(L->next, value);
        L->next->prev = L;
        return L;
    }else{
        DL_NodePtr newnode = makenode_dl(value);
        newnode->next = L;
        L->prev = newnode;
        return newnode;
    } 
}

DL_List insert_node_in_head_dl(DL_List L, DL_NodePtr node){
    node->next = L;
    if(L) L->prev = node;
    return node;
}

DL_List insert_node_in_tail_dl(DL_List L, DL_NodePtr node){
    if(!L) return node;
    L->next = insert_node_in_tail_dl(L->next, node);
    L->next->prev = L;
    return L;
}

DL_List insert_node_in_order_dl(DL_List L, DL_NodePtr node){
    if(!L) return node;
    if(node->value > L->value){
        L->next = insert_node_in_order_dl(L->next, node);
        L->next->prev = L;
        return L;
    }else{
        node->next = L;
        L->next->prev = L;
        return node;
    }
}

DL_List copy_dl(DL_List L){
    DL_NodePtr iter = L;
    DL_List Lres = makelist_dl();
    while(iter){
        Lres = insert_in_tail_dl(Lres, iter->value);
        iter = iter->next;
    }
    return Lres;
}

DL_List order_dl(DL_List L){
    DL_List Lres = makelist_dl();
    while(L){
        Lres = insert_node_in_order_dl(Lres, L);
        L = L->next;
    }
    L = drop_dl(L);
    return Lres;
}

DL_List remove_duplicates_dl(DL_List L){
    DL_NodePtr iter = L;
    DL_NodePtr tmp = NULL;
    while(iter){
        if(search_dl(L, iter->value)){
            tmp = iter;
            iter = iter->next;
            iter->prev = tmp->prev;
            free(tmp);
        }
    }
    return L;
}

void remove_with_key_dl(DL_List* L, int key){
    if(!(*L)) return;
    if((*L)->value == key){
        DL_NodePtr tmp = *L;
        *L = (*L)->next;
        (*L)->prev = tmp->prev;
        free(tmp);
        return;
    }
    remove_with_key_dl(&(*L)->next, key);
    return ;
}

const DL_NodePtr min_dl(const DL_List L){
    if(!L) return NULL;
    DL_NodePtr tmp = min_dl(L->next);
    if(!tmp) return L;
    else return (L->value > tmp->value)? tmp : L;
}
const DL_NodePtr max_dl(const DL_List L){
    if(!L) return NULL;
    DL_NodePtr tmp = min_dl(L->next);
    if(!tmp) return L;
    else return (L->value > tmp->value)? L : tmp;
}

unsigned int dl_len(const DL_List L){
    if(!L) return 0;
    return 1+dl_len(L->next);
}

int is_empty_dl(const DL_List L){
    return (L)? 1 : 0;
}

const DL_NodePtr search_dl(const DL_List L, int value){
    if(!L) return NULL;
    if(L->value == value) return L;
    else return search_dl(L->next, value);
}

void print_dl(const DL_List L){
    if(!L) return;
    printf("valore della lista: %d\n", L->value);
    print_dl(L->next);
    return;
}

DL_List drop_dl(DL_List L){
    if(!L) return L;
    L->next = drop_dl(L->next);
    free(L);
    return NULL;
}

DL_NodePtr dl_union(const DL_NodePtr L1, const DL_NodePtr L2){
    DL_NodePtr Lres = makelist_dl();
    dl_union_rec(L1, L2, &Lres);
    return Lres;
}

void dl_union_rec(const DL_NodePtr L1, const DL_NodePtr L2, DL_NodePtr* L3){
    if(!L1 && L2) dl_union_rec(L1, L2->next, L3);
    else if(L1 && L2) dl_union_rec(L1->next, L2, L3);
    else if(!L1 && !L2) return;
    if(!L1 && L2){
        if(!(*L3)) *L3 = insert_in_head_dl(*L3, L2->value);
        else if(!search_dl(*L3, L2->value)) *L3 = insert_in_head_dl(*L3, L2->value);
    }else if(L1 && L2){
        if(!search_dl(*L3, L1->value)) 
            *L3 = insert_in_head_dl(*L3, L1->value);
    }else if(L1 && !L2){
        *L3 = insert_in_head_dl(*L3, L1->value);
    }
    return;
}

DL_NodePtr dl_intersect(const DL_NodePtr L1, const DL_NodePtr L2){
    DL_NodePtr Lres = makelist_dl();
    dl_intersect_rec(L1, L2, &Lres);
    return Lres;
}

void dl_intersect_rec(const DL_NodePtr L1, const DL_NodePtr L2, DL_NodePtr* L3){
    if(L1){
        if(search_dl(L2, L1->value)){
            if(!(*L3)) *L3 = insert_in_head_dl(*L3, L1->value);
            if(!search_dl(*L3, L1->value)) *L3 = insert_in_head_dl(*L3, L1->value);
        } 
        dl_intersect_rec(L1->next, L2, L3);
    }else return;
}

DL_NodePtr dl_difference(const DL_NodePtr L1, const DL_NodePtr L2){
    DL_NodePtr Lres = makelist_dl();
    dl_difference_rec(L1, L2, &Lres);
    return Lres;
}

void dl_difference_rec(const DL_NodePtr L1, const DL_NodePtr L2, DL_NodePtr* L3){
    if(!L1) return;
    if(!search_dl(L2, L1->value)){
        if(!(*L3)) *L3 = insert_in_head_dl(*L3, L1->value);
        else if(!search_dl(*L3, L1->value)) *L3 = insert_in_head_dl(*L3, L1->value);
    }
    dl_difference_rec(L1->next, L2, L3);
    return;
}
