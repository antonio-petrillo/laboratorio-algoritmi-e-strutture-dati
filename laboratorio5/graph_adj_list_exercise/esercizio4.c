#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

void find_and_delete_cycle(graph_t g);
void find_and_delete_cycle_helper(graph_t g, path_node_ptr_t reach, unsigned int starting_point);

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
    for(unsigned int i=0; i<g->num_vertices; i++){
        reach[i].is_reach = UNREACHED;
    }
    for(unsigned int starting_point = 0; starting_point < g->num_vertices; starting_point++){
        if(reach[starting_point].is_reach == UNREACHED){
            find_and_delete_cycle_helper(g, reach, starting_point);
        }
    }
    printf("print of the DAG:\n");
    print_graph(g);
    free(reach);
    return;
}

void find_and_delete_cycle_helper(graph_t g, path_node_ptr_t reach, unsigned int starting_point){
    reach[starting_point].is_reach = REACHED_BUT_NOT_LEFT;
    for (edge_t iter = g->adj_list[starting_point]; iter != NULL; iter = iter->next){
        if(reach[iter->dest].is_reach == UNREACHED){
            find_and_delete_cycle_helper(g, reach, iter->dest);
        }else if(reach[iter->dest].is_reach == REACHED_BUT_NOT_LEFT){
            printf("the vertex %u made a cycle with the %u vertex\nremoving this edge\n", iter->dest, starting_point); 
            remove_edge(g, starting_point, iter->dest);
        }
        
    }
    reach[starting_point].is_reach = REACHED;
    return;
}