#ifndef QUEUE_STATICA_H
#define QUEUE_STATICA_H

#define MAXDIM_Q 20

/*
* per chiareza potevo definire delle nmacro per la testa e la coda
*  #define head q[0]
*  #define tail q[MAXDIM_Q + 1]
* purtroppo me ne sono reso conto tardi e ora non ho voglia di scrivere queste modifiche
*/

typedef int*  Queue;

void makequeue(Queue* q);
void freequeue(Queue* q);
int dequeue(Queue q, int* err);
void enqueue(Queue q, int value, int* err);
int is_empty(Queue q);
int is_full(Queue q);
void print(Queue q);
void print_rec(Queue q);
void reverse(Queue q);
void shift(Queue q);

#endif