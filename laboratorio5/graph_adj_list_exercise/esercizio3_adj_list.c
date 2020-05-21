#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph_adj_list.h"

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
    add_edge(g, 0, 1, 2);
    add_edge(g, 1, 2, 2);
    add_edge(g, 0, 5, 7);
    add_edge(g, 2, 1, 8);
    add_edge(g, 2, 5, 3);
    add_edge(g, 5, 2, 8);
    add_edge(g, 9, 1, 1);
    add_edge(g, 4, 6, 5);
    add_edge(g, 4, 8, 3);
    add_edge(g, 8, 7, 4);
    add_edge(g, 7, 8, 6);
    
    //edge of g_vect[0] 
    add_edge(g_vect[0], 0, 1, 4);
    add_edge(g_vect[0], 1, 2, 18);

    //edge of g_vect[1]
    add_edge(g_vect[1], 0, 1, 5);
     
    //edge of g_vect[2]
    add_edge(g_vect[2], 5, 2, 16);
    add_edge(g_vect[2], 2, 5, 21);

    //edge of g_vect[3]
    add_edge(g_vect[3], 3, 0, 1);

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
        for(edge_t iter = g_to_check->adj_list[i]; iter != NULL; iter = iter->next){
            edge_t to_compare = g->adj_list[i];
            if(to_compare == NULL && g_to_check->adj_list[i] != NULL) return 0;
            while(to_compare){
                if(iter->dest == to_compare->dest){
                    if(iter->weight % to_compare->weight != 0) {
                        return 0;
                    }
                    else{
                        break;
                    }
                }
                to_compare = to_compare->next;
            }           
        }
    }
    return 1;
}