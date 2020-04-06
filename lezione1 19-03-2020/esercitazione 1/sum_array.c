#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize srand(time(NULL))
#define random(x) rand()%x

int sum(int* vector, unsigned int dim);
int sum_rc(int* vector, unsigned int index, int accumulator);

int main(int argc, char** argv){
    randomize;
    unsigned int dim = atoi(argv[1]);
    unsigned int range = atoi(argv[2]);
    int* vector = (int*) calloc(dim, sizeof(int));
    if(!vector) exit(1);
    for(unsigned int i=0; i<dim; i++) vector[i] = random(range) * ((random(2)) ? 1 : -1);  
    for(unsigned int i=0; i<dim; i++) printf("%d\t", vector[i]);
    puts("");
    printf("the sum is %d\n", sum(vector, dim));
    free(vector);
    return 0;
}

int sum(int* vector, unsigned int dim){
    int res = sum_rc(vector, dim-1, 0);
    return res;
}

int sum_rc(int* vector, unsigned int index, int accumulator){
    if(index == 0){ accumulator += vector[0]; return accumulator; }
    accumulator += vector[index];
    return sum_rc(vector, index-1,  accumulator);
}