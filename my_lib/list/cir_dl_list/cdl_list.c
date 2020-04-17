#include <stdio.h>
#include <stdlib.h>
#include "cdl_list.h"

CDL_List makelist_cdl(){
    return NULL;
}

void cdl_error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

CDL_NodePtr makenode_cdl(int value){
    CDL_NodePtr newnode = (CDL_NodePtr) malloc(sizeof(CDL_Node));
    newnode->value = value;
    newnode->next = newnode->prev = NULL;
    newnode->head_of_the_list = NOT_HEAD;
    return newnode;
}

CDL_List insert_in_head_cdl(CDL_List L, int value){
    if(!L){
        CDL_NodePtr newnode = makenode_cdl(value);
        newnode->next = newnode->prev = newnode;
        newnode->head_of_the_list = HEAD;
        return newnode;    
    }else /*L->head_of_the_list*/{
        // I don't need to discriminate between list with one element or more
        CDL_NodePtr newnode = makenode_cdl(value);
        newnode->next = L;
        newnode->prev = L->prev;
        L->prev = newnode;
        newnode->head_of_the_list = HEAD;
        return newnode;
    }
}

CDL_List insert_in_tail_cdl(CDL_List L, int value){
    if(!L){
        CDL_NodePtr newnode = makenode_cdl(value);
        newnode->next = newnode->prev = newnode;
        newnode->head_of_the_list = HEAD;
        return newnode; 
    }else{
        CDL_NodePtr newnode = makenode_cdl(value);
        newnode->next = L;
        newnode->prev = L->prev;
        L->prev->next = newnode;
        L->prev = newnode;
        return L;
    }
}

CDL_List insert_in_order_cdl(CDL_List L, int value){
    if(!L){
        CDL_NodePtr newnode = makenode_cdl(value);
        newnode->next = newnode->prev = newnode;
        newnode->head_of_the_list = HEAD;
        return newnode; 
    }else if(L->head_of_the_list){
        if(L->value > value){
            CDL_NodePtr newnode = makenode_cdl(value);
            newnode->next = L;
            newnode->prev = L->prev;
            L->prev->next = newnode;
            L->prev = newnode;
            newnode->head_of_the_list = HEAD;
            return newnode; 
        }else{
            L->next = insert_in_order_cdl(L->next, value);
            return L;
        }
    }else if(L->next->head_of_the_list){
        if(L->value < value){
            CDL_NodePtr newnode = makenode_cdl(value);
            newnode->next = L->next;
            newnode->prev = L;
            L->next = newnode;
            newnode->next->prev = newnode;
            return L;
        }else{
            CDL_NodePtr newnode = makenode_cdl(value);
            newnode->next = L;
            newnode->prev = L->prev;
            L->prev = newnode;
            newnode->prev->next = newnode;
            return newnode;
        }
    }else if(L->value > value){
            CDL_NodePtr newnode = makenode_cdl(value);
            newnode->next = L;
            newnode->prev = L->prev;
            L->prev = newnode;
            return newnode;
    }else{//(L->value <= value)
        L->next = insert_in_order_cdl(L->next, value);
        return L;
    }
}

CDL_List insert_node_in_head_cdl(CDL_List L, CDL_NodePtr node){
    if(!L){
        node->next = node->prev = node;
        node->head_of_the_list = HEAD;
        return node;    
    }else /*L->head_of_the_list*/{
        // I don't need to discriminate between list with one element or more
        node->next = L;
        node->prev = L->prev;
        L->prev = node;
        node->head_of_the_list = HEAD;
        return node;
    }
}

CDL_List insert_node_in_tail_cdl(CDL_List L, CDL_NodePtr node){
    if(!L){
        node->next = node->prev = node;
        node->head_of_the_list = HEAD;
        return node; 
    }else{
        node->next = L;
        node->prev = L->prev;
        L->prev->next = node;
        L->prev = node;
        return L;
        return node;
    }
}

CDL_List insert_node_in_order_cdl(CDL_List L, CDL_NodePtr node){
    if(!L){
        node->next = node->prev = node;
        node->head_of_the_list = HEAD;
        return node; 
    }else if(L->head_of_the_list){
        if(L->value > node->value){
            node->next = L;
            node->prev = L->prev;
            L->prev->next = node;
            L->prev = node;
            node->head_of_the_list = HEAD;
            return node; 
        }else{
            L->next = insert_node_in_order_cdl(L->next, node);
            return L;
        }
    }else if(L->next->head_of_the_list){
        if(L->value < node->value){
            node->next = L->next;
            node->prev = L;
            L->next = node;
            node->next->prev = node;
            return L;
        }else{
            node->next = L;
            node->prev = L->prev;
            L->prev = node;
            node->prev->next = node;
            return node;
        }
    }else if(L->value > node->value){
            node->next = L;
            node->prev = L->prev;
            L->prev = node;
            return node;
    }else{//(L->value <= value)
        L->next = insert_node_in_order_cdl(L->next, node);
        return L;
    }
}

CDL_List copy_cdl(const CDL_List L){
    CDL_NodePtr iter = L;
    CDL_List Lres = makelist_cdl();
    while(iter){
        Lres = insert_in_tail_cdl(Lres, iter->value);
        if(iter->next->head_of_the_list) break;
        iter = iter->next;
    }
    return Lres;
}

CDL_List order_cdl(CDL_List L){
    if(!L) return NULL;
    L->prev->next = NULL;
    CDL_List Lres =  makelist_cdl();
    CDL_NodePtr tmp = NULL;
    while(L){
        tmp = L;
        L = L->next;
        Lres = insert_node_in_order_cdl(Lres, tmp);
    }
    L = NULL;//it isn't really needed
    return Lres;
}

CDL_List remove_duplicates_dl(CDL_List L){
    if(!L) return NULL;
    if(L == L->next) return L;
    else if(L->head_of_the_list){
        if(search_cdl(L->next, L->value)){
            CDL_NodePtr tmp = L;
            L->prev->next = L->next;
            L->next->prev = L->prev;
            L = L->next;
            L->head_of_the_list = HEAD;
            free(tmp);
            L = remove_duplicates_dl(L);
            return L;
        }else{
            L->next = remove_duplicates_dl(L->next);
            return L;
        }
    }else if(L->next->head_of_the_list){
        return L;
    }else{
        if(search_cdl(L->next, L->value)){
            CDL_NodePtr tmp = L;
            L->prev->next = L->next;
            L->next->prev = L->prev;
            L = L->next;
            L->head_of_the_list = HEAD;
            free(tmp);
            L = remove_duplicates_dl(L);
            return L;
        }else{
            L->next = remove_duplicates_dl(L->next);
            return L;
        }
    }
}

void remove_with_key_cdl(CDL_List* L, int key){
    if(!L) return;
    if((*L) == (*L)->next){
        if((*L)->value == key){
            free(*L);
            *L = NULL;
            return;
        }
        else return;
    }
    else if((*L)->head_of_the_list){
        if((*L)->value == key){// remove the head
            CDL_NodePtr tmp = *L;
            *L = (*L)->next;
            (*L)->head_of_the_list = HEAD;
            free(tmp);
            return;
        }else{//start recursion
            remove_with_key_cdl(&(*L)->next, key);
            return;
        }
    }else if((*L)->next->head_of_the_list){
        if((*L)->value == key){// remove the tail
            CDL_NodePtr tmp = *L;
            *L = (*L)->next;
            free(tmp);
            return;
        }else{//end recursion
            return;
        }
    }else{
        if((*L)->value == key){// remove the node
            CDL_NodePtr tmp = *L;
            *L = (*L)->next;
            free(tmp);
            return;
        }else{//continue recursion
            remove_with_key_cdl(&(*L)->next, key);
            return;
        }
    }
}

const CDL_NodePtr min_cdl(const CDL_List L){
    if(!L) return NULL;
    else if(L->next->head_of_the_list) return L;
    else if(L->head_of_the_list){
        CDL_NodePtr tmp = min_cdl(L->next);
        return (tmp->value > L->value) ? L : tmp;
    }else{
        CDL_NodePtr tmp = min_cdl(L->next);
        return (tmp->value > L->value) ? L : tmp;
    }
}

const CDL_NodePtr max_cdl(const CDL_List L){
    if(!L) return NULL;
    else if(L->next->head_of_the_list) return L;
    else if(L->head_of_the_list){
        CDL_NodePtr tmp = max_cdl(L->next);
        return (tmp->value < L->value) ? L : tmp;
    }else{
        CDL_NodePtr tmp = max_cdl(L->next);
        return (tmp->value < L->value) ? L : tmp;
    }
}

unsigned int cdl_len(const CDL_List L){
    if(!L) return 0;
    else if(L == L->next) return 1;
    else if(L->head_of_the_list) return 1 + cdl_len(L->next);
    else if(L->next->head_of_the_list) return 1;
    else return 1 + cdl_len(L->next);
}

int is_empty_cdl(const CDL_List L){
    return (!L) ? 1 : 0;
}

const CDL_NodePtr search_cdl(const CDL_List L, int value){
    if(!L) return NULL;
    if(L->head_of_the_list){
        if(L->value == value){
            return L;
        }else{
            return search_cdl(L->next, value);
        }
    }else if(L->next->head_of_the_list){
        if(L->value == value){
            return L;
        }else{
            return NULL;
        }
    }else{
        if(L->value == value){
            return L;
        }else{
            return search_cdl(L->next, value);
        }
    }
}

void print_cdl(const CDL_List L){
    if(!L) return;
    else if(L == L->prev /* it's the same if I write L == L->prev*/){
        printf("valore della lista:= %d\n", L->value);
        return;
    }else if(L->head_of_the_list){
        printf("valore della lista:= %d\n", L->value);
        print_cdl(L->next);
        return;
    }else if(L->next->head_of_the_list){
        printf("valore della lista:= %d\n", L->value);
        return;
    }else{  
        printf("valore della lista:= %d\n", L->value);
        print_cdl(L->next);
        return;
    }
}

CDL_List drop_cdl(CDL_List L){
    if(!L) return NULL;
    else if(L == L->prev){
        free(L);
        return NULL;
    }else if(L->head_of_the_list){
        L->next = drop_cdl(L->next);
        free(L);
        return NULL;
    }else if(L->next->head_of_the_list){
        free(L);
        return NULL;
    }else{
        L->next = drop_cdl(L->next);
        free(L);
        return NULL;
    }
}

CDL_NodePtr cdl_union(const CDL_NodePtr L1, const CDL_NodePtr L2){
    CDL_List Lres = makelist_cdl();
    cdl_union_rec(L1, L2, &Lres);
    return Lres;
}

void cdl_union_rec(const CDL_NodePtr L1, const CDL_NodePtr L2, CDL_NodePtr* L3){
    if(!L1){
        *L3 = copy_cdl(L2);
        return;
    }
    if(!L2){
        *L3 = copy_cdl(L1);
        return;
    }
    if(L1->head_of_the_list){
        *L3 = insert_in_head_cdl(*L3, L1->value);
        if(!search_cdl(*L3, L2->value)) *L3 = insert_in_head_cdl(*L3, L2->value);
        cdl_union_rec(L1->next, L2->next, L3);
        return;
    }else if(L1->next->head_of_the_list && !L2->next->head_of_the_list){
        if(!search_cdl(*L3, L1->value)) *L3 = insert_in_head_cdl(*L3, L1->value);
        if(!search_cdl(*L3, L2->value)) *L3 = insert_in_head_cdl(*L3, L2->value);
        cdl_union_rec(L1, L2->next, L3);
    }else if(!L1->next->head_of_the_list && L2->next->head_of_the_list){
        if(!search_cdl(*L3, L1->value)) *L3 = insert_in_head_cdl(*L3, L1->value);
        if(!search_cdl(*L3, L2->value)) *L3 = insert_in_head_cdl(*L3, L2->value);
        cdl_union_rec(L1->next, L2, L3);
    }else{//L1->next->head_of_the_list && L2->next->head_of_the_list
        if(!search_cdl(*L3, L1->value)) *L3 = insert_in_head_cdl(*L3, L1->value);
        if(!search_cdl(*L3, L2->value)) *L3 = insert_in_head_cdl(*L3, L2->value);
        return;
    }
}

CDL_NodePtr cdl_intersect(const CDL_NodePtr L1, const CDL_NodePtr L2){
    CDL_List Lres = makelist_cdl();
    cdl_intersect_rec(L1, L2, &Lres);
    return Lres;
}

void cdl_intersect_rec(const CDL_NodePtr L1, const CDL_NodePtr L2, CDL_NodePtr* L3){
    if(!L1 || !L2){
        return;
    }
    if(L1->head_of_the_list){
        if(search_cdl(L1, L2->value)){
            if(!search_cdl(*L3, L2->value)) 
                *L3 = insert_in_head_cdl(*L3, L2->value);
        } 
        cdl_intersect_rec(L1->next, L2->next, L3);
        return;
    }else if(L1->next->head_of_the_list && !L2->next->head_of_the_list){
        if(search_cdl(L1, L2->value)){
            if(!search_cdl(*L3, L2->value)) 
                *L3 = insert_in_head_cdl(*L3, L2->value);
        } 
        cdl_intersect_rec(L1, L2->next, L3);
    }else if(!L1->next->head_of_the_list && L2->next->head_of_the_list){
        if(search_cdl(L1, L2->value)){
            if(!search_cdl(*L3, L2->value)) 
                *L3 = insert_in_head_cdl(*L3, L2->value);
        } 
        cdl_intersect_rec(L1->next, L2, L3);
    }else{//L1->next->head_of_the_list && L2->next->head_of_the_list
        if(search_cdl(L1, L2->value)){
            if(!search_cdl(*L3, L2->value)) 
                *L3 = insert_in_head_cdl(*L3, L2->value);
        } 
        return;
    }
}

CDL_NodePtr cdl_difference(const CDL_NodePtr L1, const CDL_NodePtr L2){
    CDL_List Lres = makelist_cdl();
    cdl_difference_rec(L1, L2, &Lres);
    return Lres;
}

void cdl_difference_rec(const CDL_NodePtr L1, const CDL_NodePtr L2, CDL_NodePtr* L3){
    if(!L2){
        *L3 = copy_cdl(L1);
        return;
    }
    if(L1->head_of_the_list){
        if(!search_cdl(L1, L2->value)){
            if(!search_cdl(*L3, L1->value)) 
                *L3 = insert_in_head_cdl(*L3, L1->value);
        } 
        cdl_difference_rec(L1->next, L2->next, L3);
        return;
    }else if(L1->next->head_of_the_list && !L2->next->head_of_the_list){
        if(!search_cdl(L1, L2->value)){
            if(!search_cdl(*L3, L1->value)) 
                *L3 = insert_in_head_cdl(*L3, L1->value);
        } 
        cdl_difference_rec(L1, L2->next, L3);
    }else if(!L1->next->head_of_the_list && L2->next->head_of_the_list){
        if(!search_cdl(L1, L2->value)){
            if(!search_cdl(*L3, L1->value)) 
                *L3 = insert_in_head_cdl(*L3, L1->value);
        } 
        cdl_difference_rec(L1->next, L2, L3);
    }else{//L1->next->head_of_the_list && L2->next->head_of_the_list
        if(!search_cdl(L1, L2->value)){
            if(!search_cdl(*L3, L1->value)) 
                *L3 = insert_in_head_cdl(*L3, L1->value);
        } 
        return;
    }
}

void multi_print_cdl(const CDL_List L, int numprint){
    if(!L) return;
    CDL_NodePtr iter = L;
    int i=0;
    while (i<numprint){
        printf("valore della lista := %d\n", iter->value);
        iter = iter->next;
        if(iter->head_of_the_list) i++;
    }
}
