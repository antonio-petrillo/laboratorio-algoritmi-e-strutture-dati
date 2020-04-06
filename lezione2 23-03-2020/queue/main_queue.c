#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void remove_odd(Queue q);
void remove_odd_rec(Queue q);

int main(int argc, char** argv){
    Queue q;
    //Esercizio 1) implementazionde della coda
    makequeue(&q);
    int err;
    for(int i=0; i<10; i++) enqueue(q, i, &err);
    printf("stampa della coda con funzione apposita\n");
    print(q);
    printf("\nuso di dequeue\n");
    while(!is_empty(q)) printf("valore estratto dalla coda: %d\n", dequeue(q, &err));
    freequeue(&q);

    //Esercizio 2) rimozione dei valori dispari
    makequeue(&q);
    for(int i=0; i<10; i++) enqueue(q, i, &err);
    printf("\n\nstampa prima della rimozione\n");
    print(q);
    remove_odd(q);
    printf("\nstampa dopo della rimozione\n");
    print(q);
    freequeue(&q);
    return 0;
}

void remove_odd(Queue q){
    remove_odd_rec(q);
    reverse(q);
}

void remove_odd_rec(Queue q){
   int err;
    if(!is_empty(q)){
        int value = dequeue(q, &err);
        remove_odd_rec(q);
        if(value%2 == 0) enqueue(q, value, &err);
    }
    return;
}