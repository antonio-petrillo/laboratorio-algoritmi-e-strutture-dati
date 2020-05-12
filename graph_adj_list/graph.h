#ifndef GRAPH_H
#define GRAPH_H 1

typedef struct edge_struct{
    struct edge_struct* next;
    //void* node;
    unsigned int dest;
    int weight;
}* edge_t;


typedef struct graph_struct{
    unsigned int num_vertices;
    edge_t* adj_list;
}* graph_t;

typedef struct list_graph_node_struct{
    struct list_graph_node_struct* next;
    edge_t edge;
}* graph_list_node;

typedef struct stack_graph_struct{
    graph_list_node head;
}* graph_stack;

typedef struct queue_graph_struct{
    graph_list_node head;
    graph_list_node tail;
}* graph_queue;

graph_t make_empty_graph(unsigned int num_vertices);
edge_t make_edge(int weight, unsigned int dest);
void add_edge(graph_t G, unsigned int src, unsigned int dest, int weight);
void remove_edge(graph_t G, unsigned int src, unsigned int dest);
void print_graph(graph_t G);
void print_adj_list(edge_t l);
int is_empty_graph(graph_t G);
void drop_graph(graph_t G);
graph_t transpose(graph_t G);

graph_list_node make_graph_list_node(edge_t edge);

graph_stack make_graph_stack();
void drop_graph_stack(graph_stack s);
void push_graph_stack(graph_stack s, edge_t edge);
int pop_graph_stack(graph_stack s, edge_t* edge);

graph_queue make_graph_queue();
void drop_graph_queue(graph_queue q);
void enqueue_graph_queue(graph_queue q, edge_t edge);
int dequeue_graph_queue(graph_queue q, edge_t* edge);

/*
TODO: dijkstra, bfs, dfs, strong connected, ? min spanning tree ?
*/

#endif