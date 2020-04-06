#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize srand(time(NULL))
#define random(x) rand()%x

void print(unsigned int* vector, unsigned int dim);
void swap(unsigned int* a, unsigned int* b);
void build_heap(unsigned int* vector, unsigned int dim);
void heapify(unsigned int* vector, unsigned int dim, unsigned int sub_tree);
void heap_sort(unsigned int* vector, unsigned int dim);

int main(int argc, char** argv){
    randomize;
    unsigned int dim = atoi(argv[1]);
    unsigned int range = atoi(argv[2]);
    unsigned int* vector = (unsigned  int*) calloc(dim, sizeof(unsigned int));
    if(!vector) {printf("errore nella creazione del vettore\n"); exit(1);}
    for(int i=0; i<dim; i++) vector[i] = random(range);
    printf("stampa prima dell'ordinamento\n");
    print(vector, dim);
    heap_sort(vector, dim);
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

void swap(unsigned int* a, unsigned int* b){
    unsigned int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void build_heap(unsigned int* vector, unsigned int dim){
    for(int i=dim/2; i>=0; i--) heapify(vector, dim, i);
    return;
}

void heapify(unsigned int* vector, unsigned int dim, unsigned int sub_tree){
    unsigned int left = sub_tree*2 + 1;
    unsigned int right = sub_tree*2 + 2;
    unsigned int max;
    if(left < dim && vector[left] > vector[sub_tree]) max = left;
    else max = sub_tree;
    if(right < dim && vector[right] > vector[max]) max = right;
    if(max != sub_tree){ swap(&vector[max], &vector[sub_tree]); heapify(vector, dim, max);}
    return;
}

void heap_sort(unsigned int* vector, unsigned int dim){
    build_heap(vector, dim);
    for(int i=dim-1; i>0; i--){
        swap(&vector[0], &vector[i]);
        heapify(vector, i, 0);
    }
    return;
}