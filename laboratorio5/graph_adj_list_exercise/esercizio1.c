#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

unsigned int* indegree(graph_t g);
unsigned int* outdegree(graph_t g);

int main(int argc, char** argv){
    FILE* fp = fopen(argv[1], "r");
    assert(fp != NULL);
    graph_t g = load_graph_from_file(fp);
    fclose(fp);
    print_graph(g);
    puts("");
    free(indegree(g));
    puts("");
    free(outdegree(g));
    puts("");
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