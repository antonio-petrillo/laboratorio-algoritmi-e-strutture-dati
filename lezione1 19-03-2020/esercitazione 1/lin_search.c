#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize srand(time(NULL))
#define random(x) rand()%x

int lin_search(int* vector, int dim, int key);
int lin_search_rc(int* vector, int index, int key);

int main(int argc, char** argv){
    randomize;
    int dim = atoi(argv[1]);
    int range = atoi(argv[2]);
    int* vector = (int*) calloc(dim, sizeof(int));
    if(!vector) exit(1);
    for(unsigned int i=0; i<dim; i++) vector[i] = random(range) * ((random(2)) ? 1 : -1);  
    int key = random(range);
    printf("the vector contains the value: %d?\nAns:%s\n", key, (lin_search(vector, dim, key)) ? "true" : "false");
    free(vector);
    return 0;
}

int lin_search(int* vector, int dim, int key){
    return lin_search_rc(vector, dim-1, key);
}

int lin_search_rc(int* vector, int index, int key){
    if(index < 0) return 0;
    else if(vector[index] == key) return 1;
    else return lin_search_rc(vector, index-1, key);
}