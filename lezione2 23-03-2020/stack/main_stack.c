#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void togli_da_Stack(Stack s, int el);

int main(int argc, char** argv){
    Stack s;
    // Esercizio 1) implementazione e uso dello stack
    makestack(&s);
    int err;
    for(int i = 0; i<10; i++) push(s, si, &err);
    printf("Stampa dello stack con la funzione print\n");
    print(s);
    puts("");
    while(!is_empty(s)) printf("valore prelevato dallo stack: %d\n", pop(s, &err));
    freestack(&s);

    // Esercizio 2) eliminare ricorsivamente tutti i valori uguali a el nello stack
    //              NB: non e' necessario ottimizzare la ricorsione (tail recursion)
    makestack(&s);
    for(int i = 1; i<20; i++) push(s, i%5, &err);
    printf("\nstampa prima dell'operazione\n");
    print(s);
    togli_da_Stack(s, 4);// funzione chiave dell'esercizio 2
    printf("\nstampa dopo dell'operazione\n");
    print(s);
    freestack(&s);
    return 0;
}

void togli_da_Stack(Stack s, int el){
    int err;
    if(is_empty(s)) return;
    else{
        int element = pop(s, &err);
        togli_da_Stack(s, el);
        if(element != el) push(s, element, &err);
        return;
    }
}