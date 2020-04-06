#include <stdio.h>
#include "queue.h"

//potrei aver frainteso la traccia, non ho ben capito se i valori della coda associati a 0 vadano rimossi oppure no

void print_string(char* s, Queue q);
void print_string_rec(char* s, int index, Queue q);

int main(int argc, char** argv){
    Queue q;
    makequeue(&q);
    int err;
    for(int i=0; i<10; i++) enqueue(q, i, &err);
    char* map = "1100110011";
    printf("stringa := %s\n", map);
    print(q);
    print_string(map, q);
    print(q);
    freequeue(&q);   
    return 0;
}

void print_string(char* s, Queue q){
    puts("");
    print_string_rec(s, 0, q);
    puts("\n");
    reverse(q);
}

void print_string_rec(char* s, int index, Queue q){
    int tmp, err;
    if(s[index] == '\0') return;
    else if(s[index] == '1'){
        tmp = dequeue(q, &err);
        printf("%d\t", tmp);
        print_string_rec(s, index+1, q);
        enqueue(q, tmp, &err);
    }else{
        /*tmp = */dequeue(q, &err);
        print_string_rec(s, index+1, q);
        //enqueue(q, tmp, &err);
        //modifiche da effettuare nel caso del io abbia mal interpretato la traccia
    }
}