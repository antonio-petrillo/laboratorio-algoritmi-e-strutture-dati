#include <stdio.h>
#include <stdlib.h>

unsigned int check_prime(unsigned int n);
unsigned int check_prime_rc(unsigned int n, unsigned int index);

int main(int argc, char** argv){
    unsigned int n = atol(argv[1]);
    printf("%u is prime?\nAns: %s\n", n, (check_prime(n)) ? "true" : "false");     
    return 0;
}

unsigned int check_prime(unsigned int n){
    unsigned int index = n/2; //potrei usare anche la radice quadrata ma non ho voglia di aggiungere la libreria;
    return check_prime_rc(n, index);
}

unsigned int check_prime_rc(unsigned int n, unsigned int index){
    if(index == 1) return 1;
    else if(n % index == 0) return 0;
    else return check_prime_rc(n, index-1);
}