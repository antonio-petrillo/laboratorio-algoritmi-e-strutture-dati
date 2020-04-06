#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize srand(time(NULL))
#define random(x) rand()%x

void print(unsigned int* vector, unsigned int dim);
void inserction_sort(unsigned int* vector, unsigned int dim);

int main(int argc, char** argv){
    randomize;
    unsigned int dim = atoi(argv[1]);
    unsigned int range = atoi(argv[2]);
    unsigned int* vector = (unsigned  int*) calloc(dim, sizeof(unsigned int));
    if(!vector) {printf("errore nella creazione del vettore\n"); exit(1);}
    for(int i=0; i<dim; i++) vector[i] = random(range);
    printf("stampa prima dell'ordinamento\n");
    print(vector, dim);
    inserction_sort(vector, dim);
    printf("stampa dopo dell'ordinamento\n");
    print(vector, dim);
    free(vector);
    return 0;
}

void print(unsigned int* vector, unsigned int dim){
    for(int i=0; i<dim; i++) printf("%u\t", vector[i]);
    puts("");
    return;
}

void inserction_sort(unsigned int* vector, unsigned int dim){
    int tmp;
    int index;
    for(int i=1; i<dim; i++){
        tmp = vector[i];
        index = i-1;
        while(index>=0 && tmp < vector[index]){
            vector[index+1] = vector[index];
            index--;
        }
        vector[index+1] = tmp;
    }
    return;
}