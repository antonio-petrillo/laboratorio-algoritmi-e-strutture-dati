#ifndef STACK_STATICO_H
#define STACK_STATICO_H 1

#define MAXDIM_S 20

typedef int* Stack;

void makestack(Stack* s);
void freestack(Stack* s);
int pop(Stack s, int* err);
void push(Stack s, int value, int* err);
int is_empty(Stack s);
int is_full(Stack s);
void print(Stack s);

#endif