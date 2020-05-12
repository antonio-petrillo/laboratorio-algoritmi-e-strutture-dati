#ifndef GRAPH_H
#define GRAPH_H 1

typedef enum{WHITE, GREY, BLACK} graph_color_t;
typedef enum{UNREACHED, REACHED} reach_t;

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
    unsigned int vertex;
}* graph_list_node;

typedef struct stack_graph_struct{
    graph_list_node head;
}* graph_stack;

typedef struct queue_graph_struct{
    graph_list_node head;
    graph_list_node tail;
}* graph_queue;

typedef struct path_node_struct{
    unsigned int vertex;
    int weight;
    reach_t is_reach;
}path_node_t;

typedef path_node_t* path_node_ptr_t;

graph_t make_empty_graph(unsigned int num_vertices);
edge_t make_edge(int weight, unsigned int dest);
void add_edge(graph_t G, unsigned int src, unsigned int dest, int weight);
void remove_edge(graph_t G, unsigned int src, unsigned int dest);
void print_graph(graph_t G);
void print_adj_list(edge_t l);
int is_empty_graph(graph_t G);
void drop_graph(graph_t G);
graph_t transpose(graph_t G);

graph_list_node make_graph_list_node(unsigned int vertex);

graph_stack make_graph_stack();
void drop_graph_stack(graph_stack s);
void push_graph_stack(graph_stack s, unsigned int vertex);
int pop_graph_stack(graph_stack s, unsigned int* vertex);
int is_empty_graph_stack(graph_stack s);

graph_queue make_graph_queue();
void drop_graph_queue(graph_queue q);
void enqueue_graph_queue(graph_queue q, unsigned int vertex);
int dequeue_graph_queue(graph_queue q, unsigned int* vertex);
int is_empty_graph_queue(graph_queue q);

int is_white_graph(graph_color_t color);
int is_grey_graph(graph_color_t color);
int is_black_graph(graph_color_t color);

void bfs(graph_t G, unsigned int starting_point, unsigned int end_point);
void print_path(path_node_ptr_t reach, unsigned int starting_point, unsigned int end_point);
void print_path_helper(path_node_ptr_t reach, unsigned int starting_point, unsigned int end_point);
void dijkstra(graph_t G, unsigned int starting_point, unsigned int end_point);

graph_t load_graph_from_file(FILE* fp);

/*
TODO: dfs, strong connected, topological ordering, ? min spanning tree ?
*/

#endif
