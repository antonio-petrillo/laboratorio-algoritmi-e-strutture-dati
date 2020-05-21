#ifndef GRAPH_ADJ_MATRIX_H
#define GRAPH_ADJ_MATRIX_H 1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//typedef enum{WHITE, GREY, BLACK} graph_color_t;
typedef enum{UNREACHED, REACHED, REACHED_BUT_NOT_LEFT} reach_t;

typedef struct graph_struct{
    size_t num_vertices;
    int** adj_matrix;
}* graph_t;

typedef struct list_graph_node_struct{
    struct list_graph_node_struct* next;
    size_t vertex;
}* graph_list_node_t;

typedef struct stack_graph_struct{
    graph_list_node_t head;
}* graph_stack_t;

typedef struct queue_graph_struct{
    graph_list_node_t head;
    graph_list_node_t tail;
}* graph_queue_t;

typedef struct path_node_struct{
    unsigned int vertex;
    int weight;
    reach_t is_reach;
}path_node_t;

typedef path_node_t* path_node_ptr_t;

graph_t load_graph_from_file(FILE* fp);
graph_t make_empty_graph(size_t num_vertices);
void drop_graph(graph_t g);
void print_graph(graph_t g);
void print_full_graph_matrix(graph_t g);
void add_vertex(graph_t g);
void remove_vertex(graph_t g, size_t v);
void add_edge(graph_t g, int weight, size_t dest, size_t src);
void remove_edge(graph_t g, size_t dest, size_t src);
graph_t transpose(graph_t g);

graph_list_node_t make_graph_list_node(size_t vertex);
void print_graph_list_node(graph_list_node_t n);

graph_stack_t make_graph_stack();
void drop_graph_stack(graph_stack_t s);
void push_graph_stack(graph_stack_t s, size_t vertex);
int pop_graph_stack(graph_stack_t s, size_t* vertex);
void print_graph_stack(graph_stack_t s);
int is_empty_graph_stack(graph_stack_t s);

graph_queue_t make_graph_queue();
void drop_graph_queue(graph_queue_t q);
void enqueue_graph_queue(graph_queue_t q, size_t vertex);
int dequeue_graph_queue(graph_queue_t q, size_t* vertex);
void print_graph_queue(graph_queue_t q);
int is_empty_graph_queue(graph_queue_t q);

void bfs(graph_t g, size_t end_point, size_t starting_point);
void dijkstra(graph_t g, size_t end_point, size_t starting_point);
void print_path(path_node_ptr_t reach, size_t starting_point, size_t end_point);
void print_path_helper(path_node_ptr_t reach, size_t starting_point, size_t end_point);
void dfs(graph_t g);
void dfs_helper(graph_t g, path_node_ptr_t path, size_t starting_point);
graph_stack_t ts(graph_t g);
int ts_dfs(graph_t g, path_node_ptr_t reach, size_t starting_point, graph_stack_t s);
void set_true(int* curr, int new_candidate);
void scc(graph_t g);

/*
TODO: ? min spanning tree ?
*/

#endif
