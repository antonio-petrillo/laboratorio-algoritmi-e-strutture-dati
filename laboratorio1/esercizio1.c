#include <stdio.h>
#include <stdlib.h>

typedef struct s_node{
    int value;
    struct s_node* next;
}S_Node;

typedef S_Node* SPtr;
typedef SPtr Stack;

Stack makestack();
SPtr makestack_node(int value);
int pop(Stack* S, int* ret);
Stack push(Stack S, int value);
Stack drop_stack(Stack S);
void printstack(const Stack S);

typedef struct l_node{
    struct l_node* next;
    int value;
}L_Node;

typedef L_Node* LPtr;
typedef LPtr List;

List makelist();
LPtr makelist_node(int value);
List insert(List L, int value);
List drop_list(List L);
void printlist(const List L);

void error(char* message);
void elimina(List* L, Stack S);

int main(int argc, char** argv){
    Stack s = makestack();
    List l = makelist();
    for(int i=0; i<20; i++){
        s = push(s, (i%2)? 0 : 1);
        l = insert(l, i);
    }
    printf("stampa dello stack\n");
    printstack(s);
    printf("stampa della lista\n");
    printlist(l);
    elimina(&l, s);
    printf("stampa della lista dopo l'eliminazione\n");
    printlist(l);
    return 0;
}

void error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

Stack makestack(){
    return NULL;
}

SPtr makestack_node(int value){
    SPtr newnode = (SPtr)malloc(sizeof(S_Node));
    if(!newnode) error("error in function makestack_node");
    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

int pop(Stack* S, int* ret){
    if(*S){
        *ret = (*S)->value;
        SPtr tmp = *S;
        *S = (*S)->next;
        free(tmp);
        return 1;
    }else return 0;
}

Stack push(Stack S, int value){
    SPtr newnode = makestack_node(value);
    newnode->next = S;
    return newnode;
}

Stack drop_stack(Stack S){
    if(!S) return NULL;
    S->next = drop_stack(S->next);
    free(S);
    return NULL;
}

void printstack(const Stack S){
    if(!S) return;
    printf("stack := %d\n", S->value);
    printstack(S->next);
}

List makelist(){
    return NULL;
}

LPtr makelist_node(int value){
    LPtr newnode = (LPtr)malloc(sizeof(L_Node));
    if(!newnode) error("error in function makelist_node");
    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

List insert(List L, int value){
    LPtr newnode = makelist_node(value);
    newnode->next = L;
    return newnode;
}

List drop_list(List L){
    if(!L) return NULL;
    L->next = drop_list(L->next);
    free(L);
    return NULL;
}

void printlist(const List L){
    if(!L) return;
    printf("list := %d\n", L->value);
    printlist(L->next);
}

//assumiamo che la lista e lo stack abbiano lo stesso numero di elementi
void elimina(List* L, Stack S){
    if(!(*L)) return;
    int tmp;
    int flag = pop(&S, &tmp);
    elimina(&(*L)->next, S);
    if(flag)S = push(S, tmp);
    if(S->value && ((*L)->value%2 == 0)){
        LPtr tmpl = *L;
        *L = (*L)->next;
        free(tmpl);
    }
}