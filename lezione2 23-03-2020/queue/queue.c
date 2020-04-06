#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void makequeue(Queue* q){
    *q = (Queue)calloc(MAXDIM_Q+2, sizeof(int) /*int == 4 bytes*/);
    if(!(*q)) {perror("errore nell'allocazione della coda"); exit(EXIT_FAILURE);}
    return ;
}

void freequeue(Queue* q){
    free(*q);
    return;
}

int dequeue(Queue q, int* err){
    if(is_empty(q)){*err = 1; return 0;}
    *err = 0;
    int ret = q[q[0]];
    if(q[0] == q[MAXDIM_Q+1]){ q[0] = 0; q[MAXDIM_Q+1] = 0;}
    else q[0]++;
    return ret;
}

void enqueue(Queue q, int value, int* err){
    if(is_full(q)){
        if(q[0] == 1){
            *err = 1; 
            return;
        }else shift(q);
    }
    *err = 0;
    q[++q[MAXDIM_Q+1]] = value;
    if(q[0] == 0) q[0] = 1;
    return;
}

//L'implementazione di una coda statica e' orrenda
//Molto meglio le code dinamiche

int is_empty(Queue q){
    return q[0] == 0;
}

int is_full(Queue q){
    return q[MAXDIM_Q+1] == MAXDIM_Q;
}

void print(Queue q){
    print_rec(q);
    reverse(q);
}

void print_rec(Queue q){
    int err;
    if(!is_empty(q)){
        int value = dequeue(q, &err);
        printf("valore: %d\n", value);
        print_rec(q);
        enqueue(q, value, &err);
    }
    return;
}

void reverse(Queue q){
    int err;
    if(!is_empty(q)){
        int value = dequeue(q, &err);
        reverse(q);
        enqueue(q, value, &err);
    }
    return;
}

void shift(Queue q){
    int index = q[0];
    int range = q[MAXDIM_Q+1] - q[0] + 1;
    for(int i=1; i<range; i++) q[i] = q[index++];
    q[0] = 1;
    q[MAXDIM_Q+1] = range;  
    return;
}
