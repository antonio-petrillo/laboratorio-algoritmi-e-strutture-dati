#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

unsigned int num_of_even(Stack s);

int main(int argc, char** argv){
    Stack s;
    makestack(&s);
    int err;
    for(int i=0; i<10; i++)push(s, i, &err);
    print(s);
    printf("\nlo stack contiene %u valori pari\n\\n", num_of_even(s));
    print(s);
    freestack(&s);
    return 0;
}

unsigned int num_of_even(Stack s){
    if(is_empty(s)) return 0;
    else{
        int err;
        unsigned int res;
        int tmp = pop(s, &err);
        if(tmp%2) res = num_of_even(s);
        else res = 1+num_of_even(s);
        push(s, tmp, &err);
        return res; 
    }
}