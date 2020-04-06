#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//ho implementato la coda con 2 stack, il primo contiene effettivamente la queue, mentre il secondo lo utilizzo come temporaneo
//la semantica del primo stack e': l'elemento in testa allo stack rappresenta la testa della queue, mentre l'elemento in fondo allo stack rappresenta appunto la coda della queue
//si puo' semplicemente implementare nel senso opposto, ovvero che l'elemeto in testa dellostack e' la coda della queue, mentre quello in fondo e' la testa della queue

typedef struct{
    Stack s1;
    Stack s2;
}Queue;
 
void makequeue(Queue* q);
void freequeue(Queue* q);
int dequeue(Queue* q, int* err);
void enqueue(Queue* q, int value, int* err);
void print_queue(Queue q);

int main(int argc, char** argv){
    int err;
    Queue q;
    makequeue(&q);
    for(int i=0; i<10; i++) enqueue(&q, i, &err);
    printf("stampa della coda\n");
    print_queue(q);
    printf("\nuso della funzione dequeue\n");
    for(int i=0; i<10; i++) printf("valore estratto dalla coda: %d\n", dequeue(&q, &err));
    freequeue(&q);
    return 0; 
}

void makequeue(Queue* q){
    makestack(&(q->s1));
    makestack(&(q->s2));
    return;
}

void freequeue(Queue* q){
    freestack(&(q->s1));
    freestack(&(q->s2));
    return;
}

int dequeue(Queue* q, int* err){
    return pop(q->s1, err);
}

void enqueue(Queue* q, int value, int* err){
    //e' possibile usare lo stack delle chiamate di funzione invece di implementarlo nel codice sfruttando la ricorsione
    //ma per chiarezza ho preferito utilizzare un secondo stack                
    if(!is_full(q->s1)){
        *err = 0;
        int err2, err3;
        while(!is_empty(q->s1)) push(q->s2, pop(q->s1, &err2), &err3);
        push(q->s1, value, err);
        while(!is_empty(q->s2)) push(q->s1, pop(q->s2, &err2), err);
    }else *err = 1;
    return;
}

void print_queue(Queue q){
    int err, err2;
    print(q.s1);
    return;
}