#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "graph.h"

unsigned int* indegree(graph_t g);
unsigned int* outdegree(graph_t g);
void well_knot(graph_t g);

int main(int argc, char** argv){
    graph_t g = make_empty_graph(4);
    add_edge(g, 0, 3, 1);
    add_edge(g, 1, 3, 1);
    add_edge(g, 2, 3, 1);
    print_graph(g);
    puts("");
    well_knot(g);
    printf("\nrecall of well knot for test:\n");
    well_knot(g);
    drop_graph(g);
    return 0;
}

unsigned int* indegree(graph_t g){
    assert(g != NULL);
    unsigned int* vect = (unsigned int*) calloc(g->num_vertices, sizeof(unsigned int));
    assert(vect != NULL);
    edge_t iter = NULL;
    for(unsigned int i=0; i<g->num_vertices; i++){
        iter = g->adj_list[i];
        for( ; iter != NULL; iter = iter->next){
            vect[iter->dest]++;
        }
    }
    printf("print indegree of vertices:\n");
    for(unsigned int i=0; i<g->num_vertices; i++){
        printf("v:%2u, indegree: %u\n", i, vect[i]);
    }
    return vect;
}

unsigned int* outdegree(graph_t g){
    assert(g != NULL);
    unsigned int* vect = (unsigned int*) calloc(g->num_vertices, sizeof(unsigned int));
    assert(vect != NULL);
    edge_t iter = NULL;
    for(unsigned int i=0; i<g->num_vertices; i++){
        iter = g->adj_list[i];
        for( ; iter != NULL; iter = iter->next){
            vect[i]++;
        }
    }
    printf("print outdegree of vertices:\n");
    for(unsigned int i=0; i<g->num_vertices; i++){
        printf("v:%2u, outdegree: %u\n", i, vect[i]);
    }
    return vect;
}

//nw:at most one vertex is a well knot
void well_knot(graph_t g){
    unsigned int* in = indegree(g);
    unsigned int* out = outdegree(g);
    int has_well_knot = 0;
    for(unsigned int i=0; i<g->num_vertices; i++){
        if(in[i]==g->num_vertices-1 && out[i]==0){
            //to remove the well knot i add en edge starting from the node to an another random vertex into the graph
            printf("%u is a well knot node\n", i);
            has_well_knot = 1;
            srand(time(NULL));
            unsigned int new_end;
            do{
                new_end = rand()%g->num_vertices;
            }while (new_end == i);
            add_edge(g, i, new_end, rand()%rand()+1);
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