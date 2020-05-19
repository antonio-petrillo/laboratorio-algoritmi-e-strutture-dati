#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

size_t* indegree(graph_t g);
size_t* outdegree(graph_t g);

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