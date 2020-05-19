#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void find_and_delete_cycle(graph_t g);
void find_and_delete_cycle_helper(graph_t g, path_node_ptr_t reach, size_t starting_point);

int main(int argc, char** argv){
    FILE* fp = fopen(argv[1], "r");
    graph_t g = load_graph_from_file(fp);
    fclose(fp);
    print_graph(g);
    printf("\nsearch and delete cycle:\n");
    find_and_delete_cycle(g);
    drop_graph(g);
    return 0;
}

void find_and_delete_cycle(graph_t g){
    assert(g != NULL);
    path_node_ptr_t reach = (path_node_ptr_t) calloc(g->num_vertices, sizeof(path_node_t));
    assert(reach != NULL);
    for(size_t i=0; i<g->num_vertices; i++){
        reach[i].is_reach = UNREACHED;
    }
    for(size_t starting_point = 0; starting_point < g->num_vertices; starting_point++){
        if(reach[starting_point].is_reach == UNREACHED){
            find_and_delete_cycle_helper(g, reach, starting_point);
        }
    }
    printf("print of the DAG:\n");
    print_graph(g);
    free(reach);
    return;
}

void find_and_delete_cycle_helper(graph_t g, path_node_ptr_t reach, size_t starting_point){
    reach[starting_point].is_reach = REACHED_BUT_NOT_LEFT;
    for (size_t i = 0; i < g->num_vertices; i++){
        if(g->adj_matrix[starting_point][i] != 0){
            if(reach[i].is_reach == UNREACHED){
                find_and_delete_cycle_helper(g, reach, i);
            }else if(reach[i].is_reach == REACHED_BUT_NOT_LEFT){
                printf("the vertex %lu made a cycle with the %lu vertex\nremoving this edge\n", i, starting_point); 
                remove_edge(g, i, starting_point);
            }
        }
    }
    reach[starting_point].is_reach = REACHED;
    return;
}