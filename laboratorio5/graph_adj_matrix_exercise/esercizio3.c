#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

void check_sub_graph_multipler(graph_t g, graph_t* g_vect, size_t num_graph_to_check);
int check_single_graph(graph_t g, graph_t g_to_check);

int main(int argc, char** argv){
    graph_t g = make_empty_graph(10);
    graph_t* g_vect = (graph_t*) calloc(4, sizeof(graph_t));
    assert(g_vect != NULL);
    g_vect[0] = make_empty_graph(4);
    g_vect[1] = make_empty_graph(2);
    g_vect[2] = make_empty_graph(6);
    g_vect[3] = make_empty_graph(4);

    //edge of g
    add_edge(g, 2, 1, 0);
    add_edge(g, 2, 2, 1);
    add_edge(g, 7, 5, 0);
    add_edge(g, 8, 1, 2);
    add_edge(g, 3, 5, 2);
    add_edge(g, 8, 2, 5);
    add_edge(g, 1, 1, 9);
    add_edge(g, 5, 6, 4);
    add_edge(g, 3, 8, 4);
    add_edge(g, 4, 7, 8);
    add_edge(g, 6, 8, 7);
    
    //edge of g_vect[0] 
    add_edge(g_vect[0], 4, 1, 0);
    add_edge(g_vect[0], 18, 2, 1);

    //edge of g_vect[1]
    add_edge(g_vect[1], 5, 1, 0);
     
    //edge of g_vect[2]
    add_edge(g_vect[2], 16, 2, 5);
    add_edge(g_vect[2], 21, 5, 2);

    //edge of g_vect[3]
    add_edge(g_vect[3], 1, 0, 3);

    printf("print of g:\n");
    print_graph(g);
    puts("\nprint of g_vect[0]:");
    print_graph(g_vect[0]);
    puts("\nprint of g_vect[1]:");
    print_graph(g_vect[1]);
    puts("\nprint of g_vect[2]:");
    print_graph(g_vect[2]);
    puts("\nprint of g_vect[3]:");
    print_graph(g_vect[3]);
    puts("");

    check_sub_graph_multipler(g, g_vect, 4);

    drop_graph(g);
    drop_graph(g_vect[0]);
    drop_graph(g_vect[1]);
    drop_graph(g_vect[2]);
    drop_graph(g_vect[3]);
    free(g_vect);
    return 0;
}

void check_sub_graph_multipler(graph_t g, graph_t* g_vect, size_t num_graph_to_check){
    assert(g != NULL && g_vect != NULL);
    for(size_t i=0; i<num_graph_to_check; i++){
        if(g_vect[i]->num_vertices <= g->num_vertices && check_single_graph(g, g_vect[i])){
            printf("the %lu-th graph is a sub_multipler of g\n", i);
        }
        else{
            printf("the %lu-th graph is not a sub_multipler of g\n", i);
        }
    }
    return;
}

int check_single_graph(graph_t g, graph_t g_to_check){
    int is_sub_multipler = 1;
    assert(g != NULL && g_to_check != NULL);
    for(size_t i=0; i<g_to_check->num_vertices; i++){
        for(size_t j=0; j<g_to_check->num_vertices; j++){
            if(g->adj_matrix[i][j] != 0){
                if(g_to_check->adj_matrix[i][j]%g->adj_matrix[i][j] != 0){
                    is_sub_multipler = 0;
                    break;
                }
            }else{
                if(g_to_check->adj_matrix[i][j] != 0){
                    is_sub_multipler = 0;
                    break;
                }
            }
            
        }
    }
    return is_sub_multipler;
}