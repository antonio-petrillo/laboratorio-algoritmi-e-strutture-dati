#include <stdio.h>
#include <stdlib.h>

unsigned long long int factorial(unsigned long long int n);

int main(int argc, char** argv){
    unsigned long long int n = atoi(argv[1]);
    printf("the factorial of %llu is: %llu\n", n, factorial(n));
    return 0;
}

unsigned long long int factorial(unsigned long long int n){
    if(n == 1 || n == 0) return 1;
    return n*factorial(n-1);
}