#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

graph_t make_empty_graph(unsigned int num_vertices){
    graph_t g = (graph_t) malloc(sizeof(struct graph_struct));
    assert(g != NULL);
    g->num_vertices = num_vertices;
    g->adj_matrix = (int**) calloc(num_vertices, sizeof(int*));
    assert(g->adj_matrix != NULL);
    for(unsigned int i=0; i<num_vertices; i++){
        g->adj_matrix[i] = (int*) calloc(num_vertices, sizeof(int));
        assert(g->adj_matrix[i]);
    }
    return g;
}

void add_edge(graph_t G, unsigned int src, unsigned int dest, int weight){
    assert(G != NULL);
    G->adj_matrix[src][dest] = weight;
    return;
}

void remove_edge(graph_t G, unsigned int src, unsigned int dest);

void print_graph(graph_t G){
    assert(G != NULL);
    for(unsigned int i=0; i < G->num_vertices; i++){
        printf("ADJ_LIST[%u]: ", i);
        for(unsigned int j=0; j < G->num_vertices; j++){
            if(G->adj_matrix[i][j]){
                printf("(dest: %u, weight: %d)", j, G->adj_matrix[i][j]);
            }
        }
        printf("--/\n");
    }
    return;
}

int is_empty_graph(graph_t G);

void drop_graph(graph_t G){
    for(unsigned int i=0; i < G->num_vertices; i++){
        free(G->adj_matrix[i]);
    }
    free(G->adj_matrix);
    free(G);
    G = NULL;
    return;
}

graph_t transpose(graph_t G);

void remove_vertex(graph_t G, unsigned int v);//logical remove
void add_vertex(graph_t G);

graph_list_node_t make_graph_list_node(unsigned int vertex);
void print_graph_list_node(graph_list_node_t n);

graph_stack_t make_graph_stack();
void drop_graph_stack(graph_stack_t s);
void push_graph_stack(graph_stack_t s, unsigned int vertex);
int pop_graph_stack(graph_stack_t s, unsigned int* vertex);
void print_graph_stack(graph_stack_t s);
int is_empty_graph_stack(graph_stack_t s);

graph_queue_t make_graph_queue();
void drop_graph_queue(graph_queue_t q);
void enqueue_graph_queue(graph_queue_t q, unsigned int vertex);
int dequeue_graph_queue(graph_queue_t q, unsigned int* vertex);
void print_graph_queue(graph_queue_t q);
int is_empty_graph_queue(graph_queue_t q);

int is_white_graph(graph_color_t color);
int is_grey_graph(graph_color_t color);
int is_black_graph(graph_color_t color);

void bfs(graph_t G, unsigned int starting_point, unsigned int end_point);
void print_path(path_node_ptr_t reach, unsigned int starting_point, unsigned int end_point);
void print_path_helper(path_node_ptr_t reach, unsigned int starting_point, unsigned int end_point);
void dijkstra(graph_t G, unsigned int starting_point, unsigned int end_point);

graph_t load_graph_from_file(FILE* fp){
	unsigned int num_vertices;
	unsigned int src, dest;
	int weight;
	fscanf(fp, "%u", &num_vertices);
	graph_t g = make_empty_graph(num_vertices);
	while(!feof(fp)){
		fscanf(fp, "%u", &src);
		fscanf(fp, "%u", &dest);
		fscanf(fp, "%d", &weight);
		add_edge(g, src, dest, weight);
	}
	return g;

    /*
    first line: --> num_vertices
    loop: first:  --> src
          second: --> sdest
          third:  --> weight
    */

}

void dfs(graph_t G);
void dfs_helper(graph_t G, path_node_ptr_t path, unsigned int starting_point);

graph_stack_t ts(graph_t G);
int ts_dfs(graph_t G, path_node_ptr_t reach, unsigned int starting_point, graph_stack_t s);
void set_true(int* curr, int new_candidate);

void scc(graph_t G);