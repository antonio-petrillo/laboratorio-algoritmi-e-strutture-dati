#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "graph_adj_matrix.h"

void well_knot(graph_t g);

int main(int argc, char** argv){
    graph_t g = make_empty_graph(4);
    add_edge(g, 1, 3, 0);
    add_edge(g, 1, 3, 1);
    add_edge(g, 1, 3, 2);
    print_graph(g);
    puts("");
    well_knot(g);
    printf("\nrecall of well knot for test:\n");
    well_knot(g);
    drop_graph(g);
    return 0;
}

void well_knot(graph_t g){
    srand(time(NULL));
    size_t candidate;
    int found = 0;
    for(size_t i=0; i < g->num_vertices; ){
        candidate = i;
        for(size_t j=i; i < g->num_vertices; j++){
            if(g->adj_matrix[i][j] != 0){
                i = j;
                break;
            }
            if(j==g->num_vertices-1) found = 1;
        }
        if(found) break;
    }
    printf("candidate %lu\n", candidate);
    for(size_t i=0; i<g->num_vertices; i++){
        if(g->adj_matrix[candidate][i] != 0 && i != candidate){
            printf("this graph doesn't have a well knot node\n");
            return;
        }
    }
    printf("%lu is a well knot node\n", candidate);
    size_t dest;
    do{
        dest = rand()%g->num_vertices;
    }while(dest == candidate);
    add_edge(g, rand()%rand(), dest, candidate);
    return;
}