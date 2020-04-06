#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void makestack(Stack* s){
    *s = (Stack)calloc(MAXDIM_S+1, sizeof(int)/* == 4 bytes*/);
    if(!(*s)){perror("errrore nella creazione dello stack"); exit(1);}
    return;
}

void freestack(Stack* s){
    free(*s);
    return;
}

int pop(Stack s, int* err){
    if(is_empty(s)){*err = 1; return 0;}
    *err = 0;
    return s[s[0]--];
}

void push(Stack s, int value, int* err){
    if(is_full(s)){*err = 1; return;}
    *err = 0;
    s[++s[0]] = value;
    return;
}

int is_empty(Stack s){
    return s[0] == 0;
}

int is_full(Stack s){
    return s[0] == MAXDIM_S;
}

void print(Stack s){
    //non sto eseguendo controlli sul parametro err, per semplicita'
    // anche perche' le funzioni di pop e push effettuano dei controlli interni
    int err;
    if(is_empty(s)) return;
    else{
        int value_to_be_printed = pop(s, &err);
        printf("valore: %d\n", value_to_be_printed);
        print(s);
        push(s, value_to_be_printed, &err);
        return;
    }
}