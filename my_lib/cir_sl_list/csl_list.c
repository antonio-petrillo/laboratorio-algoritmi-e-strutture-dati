#include <stdio.h>
#include <stdlib.h>
#include "csl_list.h"

CSL_List makelist_csl(){
    return NULL;
}

void csl_error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

CSL_NodePtr makenode_csl(int value){
    CSL_NodePtr newnode = (CSL_NodePtr) malloc(sizeof(CSL_Node));
    if(!newnode) csl_error("error in function makenode_csl");
    newnode->next = NULL;
    newnode->value = value;
    newnode->head_of_the_list = NOT_HEAD;
    return newnode;
}

CSL_NodePtr* search_last_sl(CSL_List* L){
    if(!(*L)) return NULL;
    else if((*L)->next->head_of_the_list) return &(*L);
    else return search_last_sl(&(*L)->next); 
}

CSL_List insert_in_head_csl(CSL_List L, int value){
    CSL_NodePtr newnode = makenode_csl(value);
    newnode->head_of_the_list = HEAD;
    if(!L){//empty list
        newnode->next = newnode;
        return newnode;
    }
    else{//not empty list 
        // search_previous_head find the pointer to the 'last' element of teh list
        newnode->next = L;
        CSL_NodePtr* tmp = search_last_sl(&L);
        (*tmp)->next = newnode;
        L->head_of_the_list = NOT_HEAD;
    }  
    return newnode; 
}

CSL_List insert_in_tail_csl(CSL_List L, int value){
    if(!L){// empty list
        CSL_NodePtr newnode = makenode_csl(value);
        newnode->next = newnode;
        newnode->head_of_the_list = HEAD;
        return newnode;
    }else if(L == L->next){// list with one element
        CSL_NodePtr newnode = makenode_csl(value);
        newnode->next = L;
        L->next = newnode;
        return L;
    }
    else if(L->head_of_the_list){// if this is the head node start recursion
        L->next = insert_in_tail_csl(L->next, value);
        return L;
    }else if(L->next->head_of_the_list){// if this is the last node before the haed of the list
        CSL_NodePtr newnode = makenode_csl(value);
        newnode->next = L->next;
        return newnode;
    }else{// continue recursion
        L->next = insert_in_tail_csl(L->next, value);
        return L;
    }
}

CSL_List insert_in_order_csl(CSL_List L, int value){
    if(!L){// empty list
        CSL_NodePtr newnode = makenode_csl(value);
        newnode->next = newnode;
        newnode->head_of_the_list = HEAD;
        return newnode;
    }else if(L == L->next){// list with one element
        CSL_NodePtr newnode = makenode_csl(value);
        if(value > L->value){// insert in tail
            L->next = newnode;
            newnode->next = L;
            return L;
        }else{ // insert in head
            newnode->next = L;
            L->next = newnode;
            L->head_of_the_list = NOT_HEAD;
            newnode->head_of_the_list = HEAD;
            return newnode;
        }
    }else if(L->head_of_the_list){// if this is the head node start recursion 
                                  // and the list has more than 1 node
        if (L->value > value){// insert
            CSL_NodePtr newnode = makenode_csl(value);
            newnode->next = L;
            newnode->head_of_the_list = HEAD;
            CSL_NodePtr* tmp = search_last_sl(&L);
            L->head_of_the_list = NOT_HEAD;
            (*tmp)->next = newnode;
            return newnode;
        }else{// start recursion
            L->next = insert_in_order_csl(L->next, value);
            return L;
        }
    }else if(L->next->head_of_the_list){
        if(L->value < value){
            CSL_NodePtr newnode = makenode_csl(value);
            newnode->next = L->next;
            L->next = newnode;
            return L;
        }else{
            CSL_NodePtr newnode = makenode_csl(value);
            newnode->next = L;
            return newnode;
        }
    }else if(L->value > value){ // found correct location
        CSL_NodePtr newnode = makenode_csl(value);
        newnode->next = L->next;
        L->next = newnode;
        return L;
    }else{// continue recursion (value < L->value)
        L->next = insert_in_order_csl(L->next, value);
        return L;
    }
}

CSL_List insert_node_in_head_csl(CSL_List L, CSL_NodePtr node){
    node->head_of_the_list = HEAD;
    if(!L){//empty list
        node->next = node;
        return node;
    }
    else{//not empty list 
        // search_previous_head find the pointer to the 'last' element of teh list
        node->next = L;
        CSL_NodePtr* tmp = search_last_sl(&L);
        (*tmp)->next = node;
        L->head_of_the_list = NOT_HEAD;
    }  
    return node; 
}

CSL_List insert_node_in_tail_csl(CSL_List L, CSL_NodePtr node){
    if(!L){// empty list
        node->next = node;
        node->head_of_the_list = HEAD;
        return node;
    }else if(L == L->next){// list with one element
        node->next = L;
        L->next = node;
        return L;
    }
    else if(L->head_of_the_list){// if this is the head node start recursion
        L->next = insert_node_in_tail_csl(L->next, node);
        return L;
    }else if(L->next->head_of_the_list){// if this is the last node before the haed of the list
        node->next = L->next;
        return node;
    }else{// continue recursion
        L->next = insert_node_in_tail_csl(L->next, node);
        return L;
    }
}

CSL_List insert_node_in_order_csl(CSL_List L, CSL_NodePtr node){
    if(!L){// empty list
        node->next = node;
        node->head_of_the_list = HEAD;
        return node;
    }else if(L == L->next){// list with one element
        if(node->value > L->value){// insert in tail
            L->next = node;
            node->next = L;
            return L;
        }else{ // insert in head
            node->next = L;
            L->next = node;
            L->head_of_the_list = NOT_HEAD;
            node->head_of_the_list = HEAD;
            return node;
        }
    }else if(L->head_of_the_list){// if this is the head node start recursion 
                                  // and the list has more than 1 node
        if (L->value > node->value){// insert
            node->next = L;
            node->head_of_the_list = HEAD;
            CSL_NodePtr* tmp = search_last_sl(&L);
            L->head_of_the_list = NOT_HEAD;
            (*tmp)->next = node;
            return node;
        }else{// start recursion
            L->next = insert_node_in_order_csl(L->next, node);
            return L;
        }
    }else if(L->next->head_of_the_list){
        if(L->value < node->value){
            node->next = L->next;
            L->next = node;
            return L;
        }else{
            node->next = L;
            return node;
        }
    }else if(L->value > node->value){ // found correct location
        node->next = L->next;
        L->next = node;
        return L;
    }else{// continue recursion (value < L->value)
        L->next = insert_node_in_order_csl(L->next, node);
        return L;
    }
}

CSL_List copy_csl(const CSL_List L){
    CSL_NodePtr iter = L;
    CSL_List Lres = makelist_csl();
    while(iter){
        Lres = insert_in_tail_csl(L, iter->value);
        iter = iter->next;
    }
    return Lres;
}

CSL_List order_csl(CSL_List L){
    CSL_List Lres = makelist_csl();
    CSL_NodePtr iter = L;
    CSL_NodePtr* last = search_last_sl(&L);
    (*last)->next = NULL; //I turn the circular list into a normal list
    while(iter){
        Lres = insert_node_in_order_csl(Lres, iter);
        iter = iter->next;
    }
    L = NULL;// it really isn't needed
    return Lres;
}

CSL_List remove_duplicates_sl(CSL_List L){
    if(!L) return NULL;
    else if(L == L->next) return L;
    else if(L->head_of_the_list){
        if(search_csl(L->next, L->value)){//delete head node
            CSL_NodePtr tmp = L;
            CSL_NodePtr* prev = search_last_sl(&L);
            (*prev)->next = L->next;
            L->head_of_the_list = HEAD;
            L = L->next;
            free(tmp);
            L = remove_duplicates_sl(L);//start recursion
        }else{
            L->next = remove_duplicates_sl(L->next);//start recursion 
        }
        return L;
    }else if(L->next->head_of_the_list){// end recursion
        return L;
    }else{// continue recursion
        if(search_csl(L->next, L->value)){
            CSL_NodePtr tmp = L;
            L = L->next;
            free(L);
            L = remove_duplicates_sl(L);// continue recursion
        }else{
            L->next = remove_duplicates_sl(L->next);// continue recursion
        }
        return L;
    }
}

void remove_with_key_csl(CSL_List* L, int key){
    if(!(*L)) return;
    else if((*L)->head_of_the_list){
        if((*L)->value == key){// remove head and return
            CSL_NodePtr tmp = *L;
            CSL_NodePtr* prev = search_last_sl(L);
            (*prev)->next = (*L)->next;
            *L = (*L)->next;
            (*L)->head_of_the_list = HEAD;
            free(tmp);
            return;
        }else{//start recursion
            remove_with_key_csl(L, key);
            return;
        }
    }else if((*L)->next->head_of_the_list){
        if((*L)->value == key){// remove last
            CSL_NodePtr tmp = *L;
            *L = (*L)->next;
            free(tmp);
            return;
        }else return;//end recursion
    }else{
        if((*L)->value == key){//node found
            CSL_NodePtr tmp = *L;
            *L = (*L)->next;
            free(tmp);
            return;
        }else{//continue recursion
            remove_with_key_csl(L, key);
            return;
        }
    }   
}

const CSL_NodePtr min_csl(const CSL_List L){
    if(!L) return NULL;
    else if(L == L->next){
        return L;
    }else if(L->head_of_the_list){
        CSL_NodePtr tmp = min_csl(L->next);
        return (tmp->value < L->value) ? tmp : L;
    }else if(L->next->head_of_the_list){
        return L;
    }else{
        CSL_NodePtr tmp = min_csl(L->next);
        return (tmp->value < L->value) ? tmp : L;
    }
}

const CSL_NodePtr max_csl(const CSL_List L){
    if(!L) return NULL;
    else if(L == L->next){
        return L;
    }else if(L->head_of_the_list){
        CSL_NodePtr tmp = max_csl(L->next);
        return (tmp->value > L->value) ? tmp : L;
    }else if(L->next->head_of_the_list){
        return L;
    }else{
        CSL_NodePtr tmp = max_csl(L->next);
        return (tmp->value > L->value) ? tmp : L;
    }
}

unsigned int csl_len(const CSL_List L){
    if(!L) return 0;
    else if(L == L->next) return 1;
    else if(L->head_of_the_list) return 1 + csl_len(L->next);
    else if(L->next->head_of_the_list) return 1;
    else return 1 + csl_len(L->next); 
}

int is_empty_csl(const CSL_List L){
    return (L) ? 1 : 0;
}

const CSL_NodePtr search_csl(const CSL_List L, int value){
    if(!L) return NULL;
    else if(L == L->next){
        if(L->value == value) return L;
        else return NULL;
    }else if(L->head_of_the_list){
        if(L->value == value) return L;
        else return search_csl(L->next, value);
    }else if(L->next->head_of_the_list){
        if(L->value == value) return L;
        else return NULL;
    }else{
        if(L->value == value) return L;
        else return search_csl(L->next, value);
    }
}

void print_csl(const CSL_List L){
    if(!L) return;
    else if(L == L->next){
        printf("valore della lista := %d\n", L->value);
        return;
    }else if(L->head_of_the_list){
        printf("valore della lista := %d\n", L->value);
        print_csl(L->next);
        return;
    }else if(L->next->head_of_the_list){
        printf("valore della lista := %d\n", L->value);
        return;
    }else{
        printf("valore della lista := %d\n", L->value);
        print_csl(L->next);
        return;
    }
}

CSL_List drop_csl(CSL_List L){
    if(!L) return NULL; //empty list
    else if(L == L->next){
        free(L);
        return NULL;
    }else if(L->head_of_the_list){ // start recursion
        L->next = drop_csl(L->next);
        free(L);
        return NULL;
    }else if(L->next->head_of_the_list){//start delete, or in other word end recursion
        free(L);
        return NULL;
    }else{// continue recursion
        L->next = drop_csl(L->next);
        free(L);
        return NULL;
    }
}

CSL_NodePtr csl_union(const CSL_NodePtr L1, const CSL_NodePtr L2){
    CSL_List L3 = makelist_csl();
    csl_union_rec(L1, L2, &L3);
    return L3;
}

void csl_union_rec(const CSL_NodePtr L1, const CSL_NodePtr L2, CSL_NodePtr* L3){
    if(!L1) {
        *L3 = copy_csl(L2);
        *L3 = remove_duplicates_sl(*L3);
        return;    
    }else if(!L2){
        *L3 = copy_csl(L1);
        *L3 = remove_duplicates_sl(*L3);
        return;
    }else if(L1->head_of_the_list/* && L2->head_of_the_list*/){// start recursion on list 1 and list 2
        *L3 = insert_in_head_csl(*L3, L1->value);
        if(!search_csl(*L3, L2->value)) *L3 = insert_in_head_csl(*L3, L2->value);
        csl_union_rec(L1->next, L2->next, L3);
        return;
    }else if(!L1->next->head_of_the_list && !L2->next->head_of_the_list){
        if(!search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L1->value);
        if(!search_csl(*L3, L2->value)) *L3 = insert_in_head_csl(*L3, L2->value);
        csl_union_rec(L1->next, L2->next, L3);
        return;
    }else if(!L1->next->head_of_the_list && L2->next->head_of_the_list){
        if(!search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L1->value);
        if(!search_csl(*L3, L2->value)) *L3 = insert_in_head_csl(*L3, L2->value);
        csl_union_rec(L1->next, L2, L3);
        return;
    }else if(L1->next->head_of_the_list && !L2->next->head_of_the_list){
        if(!search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L1->value);
        if(!search_csl(*L3, L2->value)) *L3 = insert_in_head_csl(*L3, L2->value);
        csl_union_rec(L1, L2->next, L3);
        return;
    }else{//L1->next->head_of_the_list && L2->next->head_of_the_list
        if(!search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L1->value);
        if(!search_csl(*L3, L2->value)) *L3 = insert_in_head_csl(*L3, L2->value);
        return;
    }
}

CSL_NodePtr csl_intersect(const CSL_NodePtr L1, const CSL_NodePtr L2){
    CSL_List L3 = makelist_csl();
    csl_intersect_rec(L1, L2, &L3);
    return L3;
}

void csl_intersect_rec(const CSL_NodePtr L1, const CSL_NodePtr L2, CSL_NodePtr* L3){
    if(!L1 || !L2) return;
    else if(L1->head_of_the_list /*L2->head_of_the_list*/){
        if(search_csl(L2, L1->value) && !search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L1->value);
        csl_intersect_rec(L1->next, L2->next, L3);
        return;
    }else if(!L1->next->head_of_the_list && !L2->next->head_of_the_list){
        if(search_csl(L2, L1->value) && !search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L1->value);
        csl_intersect_rec(L1->next, L2->next, L3);
        return;
    }else if(L1->next->head_of_the_list && !L2->next->head_of_the_list){
        if(search_csl(L2, L1->value) && !search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L1->value);
        return;
    }else if(!L1->next->head_of_the_list && L2->next->head_of_the_list){
        if(search_csl(L1, L2->value) && !search_csl(*L3, L2->value)) *L3 = insert_in_head_csl(*L3, L2->value);
        return;
    }else{//L1->next->head_of_the_list && L2->next->head_of_the_list
        if(search_csl(L1, L2->value) && !search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L2->value);
        return;
    }
}

CSL_NodePtr csl_difference(const CSL_NodePtr L1, const CSL_NodePtr L2){
    CSL_List L3 = makelist_csl();
    csl_difference_rec(L1, L2, &L3);
    return L3;
}

void csl_difference_rec(const CSL_NodePtr L1, const CSL_NodePtr L2, CSL_NodePtr* L3){
    if(!L1) return;
    else if(!L2){
        *L3 = copy_csl(L1);
    }else if(L1->head_of_the_list /* && L2->head_of_the_list*/){
        if(!search_csl(L2, L1->value) && !search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L1->value);
        csl_difference_rec(L1->next, L2, L3);
        return;
    }else if(L1->next->head_of_the_list){
        if(!search_csl(L2, L1->value) && !search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L1->value);
        return;
    }else{ //!L1->next->head_of_the_list
        if(!search_csl(L2, L1->value) && !search_csl(*L3, L1->value)) *L3 = insert_in_head_csl(*L3, L1->value);
        csl_difference_rec(L1->next, L2, L3);
        return;
    }
}

void multi_print_csl(const CSL_List L, int numprint){
    if(!L) return;
    CSL_NodePtr iter = L;
    int i=0;
    while ( i<numprint){
        printf("valore della lista := %d\n", iter->value);
        iter = iter->next;
        if(iter->head_of_the_list) i++;
    }
}