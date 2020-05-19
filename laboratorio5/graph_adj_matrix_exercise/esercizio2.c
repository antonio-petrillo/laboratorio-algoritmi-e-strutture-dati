#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "graph.h"

size_t* indegree(graph_t g);
size_t* outdegree(graph_t g);

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

size_t* indegree(graph_t g){
    assert(g != NULL);
    size_t* vect = (size_t*) calloc(g->num_vertices, sizeof(size_t));
    assert(vect != NULL);
    for(size_t i=0; i<g->num_vertices; i++){
        for(size_t j=0; j<g->num_vertices; j++){
            if(g->adj_matrix[i][j] != 0){
                vect[j]++;
            }
        }
    }
    printf("print indegree of vertices:\n");
    for(size_t i=0; i<g->num_vertices; i++){
        printf("v:%2lu, indegree: %lu\n", i, vect[i]);
    }
    return vect;
}

size_t* outdegree(graph_t g){
    assert(g != NULL);
    size_t* vect = (size_t*) calloc(g->num_vertices, sizeof(size_t));
    assert(vect != NULL);
    for(size_t i=0; i<g->num_vertices; i++){
        for(size_t j=0; j<g->num_vertices; j++){
            if(g->adj_matrix[i][j] != 0){
                vect[i]++;
            }
        }
    }
    printf("print outdegree of vertices:\n");
    for(size_t i=0; i<g->num_vertices; i++){
        printf("v:%2lu, outdegree: %lu\n", i, vect[i]);
    }
    return vect;
}

void well_knot(graph_t g){
    size_t* in = indegree(g);
    size_t* out = outdegree(g);
    int has_well_knot = 0;
    for(size_t i=0; i<g->num_vertices; i++){
        if(in[i]==g->num_vertices-1 && out[i]==0){
            //to remove the well knot i add en edge starting from the node to an another random vertex into the graph
            printf("%lu is a well knot node\n", i);
            has_well_knot = 1;
            srand(time(NULL));
            size_t new_end;
            do{
                new_end = rand()%g->num_vertices;
            }while (new_end == i);
            add_edge(g, rand()%rand(), new_end, i);
            break;
        }
    }
    if(!has_well_knot){
        printf("this graph doesn't have a well knot node\n");
    }else{
        printf("modified graph:\n");
        print_graph(g);
    }
    free(in);
    free(out);
    return;
}