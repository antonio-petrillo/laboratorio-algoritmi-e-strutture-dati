#include <stdio.h>
#include "queue.h"

unsigned int num_of_odd(Queue q);
unsigned int num_of_odd_rec(Queue q);

int main(int argc, char** argv){
    Queue q;
    makequeue(&q);
    int err;
    for(int i=0; i<10; i++)enqueue(q, i, &err);
    print(q);
    printf("\nla coda contiene %u valori dispari\n\n", num_of_odd(q));
    print(q);
    freequeue(&q);
    return 0;
}

unsigned int num_of_odd(Queue q){
    int res = num_of_odd_rec(q);
    reverse(q);
    return res;
}

unsigned int num_of_odd_rec(Queue q){
    if(is_empty(q)) return 0;
    else{
        int err;
        unsigned int res;
        int tmp = dequeue(q, &err);
        if(tmp%2) res = 1+num_of_odd_rec(q);
        else res = num_of_odd_rec(q);
        enqueue(q, tmp, &err);
        return res; 
    }
}