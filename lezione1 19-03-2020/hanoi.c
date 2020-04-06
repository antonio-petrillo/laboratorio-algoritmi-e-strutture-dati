//non e' stato presentato questo esercizio durante la lezione, ma questo esercizio mi diverte troppo

#include <stdio.h>
#include <stdlib.h>

void hanoi(unsigned int n, char a, char b, char c);

int main(int argc, char** argv){
    hanoi(atoi(argv[1]), 'A', 'B', 'C');
    return 0;
}

void hanoi(unsigned int n, char a, char b, char c){
    if(n == 1){
        printf("move disk 1 from %c to %c\n", a, b);
        return;
    }
    hanoi(n-1, a, c, b);
    printf("move disk %u from %c to %c\n", n, a, b);
    hanoi(n-1, c, b, a);
}