#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

graph_t make_empty_graph(unsigned int num_vertices){
    graph_t new_g = (graph_t) malloc(sizeof(struct graph_struct));
    assert(new_g != NULL);
    new_g->num_vertices = num_vertices;
    new_g->adj_list = (edge_t*)calloc(num_vertices, sizeof(edge_t));
    assert(new_g->adj_list != NULL);
    for(unsigned int i=0; i<num_vertices; i++) new_g->adj_list[i] = NULL;
    return new_g;
}

edge_t make_edge(int weight, unsigned int dest){
    edge_t new_edge = (edge_t) malloc(sizeof(struct edge_struct));
    assert(new_edge != NULL);
    new_edge->dest = dest;
    new_edge->weight = weight;
    new_edge->next = NULL;
    return new_edge;
}

void add_edge(graph_t G, unsigned int src, unsigned int dest, int weight){
    edge_t new_edge = make_edge(weight, dest);
    new_edge->next = G->adj_list[src];
    G->adj_list[src] = new_edge;
    return;
}

void remove_edge(graph_t G, unsigned int src, unsigned int dest){
    edge_t* iter = &G->adj_list[src];
    while((*iter) != NULL &&  (*iter)->dest != dest) iter = &(*iter)->next;
    if((*iter) != NULL){
        edge_t tmp = *iter;
        *iter = (*iter)->next;
        free(tmp);
    }
    return;
}

void print_graph(graph_t G){
    for(unsigned int i=0; i<G->num_vertices; i++){
        printf("ADJ_LIST[%d]: ", i);
        print_adj_list(G->adj_list[i]);
    }
    return;
}

void print_adj_list(edge_t l){
    if(l){
        printf("(dest: %d, weight: %d)  ", l->dest, l->weight);
        print_adj_list(l->next);
    }else{
        printf("--/\n");
    }
    return;
}

int is_empty_graph(graph_t G){
    return G == NULL;
}

void drop_graph(graph_t G){
    if(G != NULL){
        edge_t iter, tmp;
        for(unsigned int i=0; i<G->num_vertices; i++){
            iter = G->adj_list[i];
            while(iter){
                tmp = iter;
                iter = iter->next;
                free(tmp);
            }
        }
        free(G->adj_list);
        free(G);
        G = NULL;
    }
    return;
}

graph_t transpose(graph_t G){
    graph_t transpose = make_empty_graph(G->num_vertices);
    for(unsigned int i=0; i<G->num_vertices; i++){
        edge_t iter = G->adj_list[i];
        while(iter){
            add_edge(transpose, iter->dest, i, iter->weight);
            iter = iter->next;
        }
    }
    return transpose;
}

void remove_vertex(graph_t G, unsigned int v){ // logical remove
    if(G != NULL){
        if(v < G->num_vertices){
            edge_t tmp = NULL;
            for(edge_t iter = G->adj_list[v]; iter != NULL; ){
                tmp = iter;
                iter = iter->next;
                free(tmp);
            }
            G->adj_list[v] = NULL;
            for(unsigned int i = 0; i < G->num_vertices; i++){
                edge_t iter = G->adj_list[i];
                if(i == v) continue;
                while(iter){
                    if(iter->dest == v){
                        remove_edge(G, i,  v);
                    }
                    iter = iter->next;
                }
            }
        }
    } 
    return;
}

void add_vertex(graph_t G){
    G->num_vertices++;
    edge_t* new_adj_list = (edge_t*) calloc(G->num_vertices, sizeof(edge_t));
    assert(new_adj_list != NULL);
    for(unsigned int i=0; i < G->num_vertices-1; i++){
        new_adj_list[i] = G->adj_list[i];
        G->adj_list[i] = NULL;
    }
    free(G->adj_list);
    G->adj_list = new_adj_list;
    return;
}

graph_stack_t make_graph_stack(){
    graph_stack_t s = (graph_stack_t) malloc(sizeof(struct stack_graph_struct));
    assert(s != NULL);
    s->head = NULL;
    return s;
}


graph_list_node_t make_graph_list_node(unsigned int vertex){
    graph_list_node_t newnode = (graph_list_node_t) malloc(sizeof(struct list_graph_node_struct));
    assert(newnode != NULL);
    newnode->next = NULL;
    newnode->vertex = vertex;
    return newnode;
}

void print_graph_list_node(graph_list_node_t n){
    if(n){
        printf(" %u", n->vertex);
        print_graph_list_node(n->next);
    }
    else{
        printf("\n");
    }
    return;
}

void drop_graph_stack(graph_stack_t s){
    graph_list_node_t tmp = NULL, iter = s->head;
    while(iter){
        tmp = iter; 
        iter = iter->next;
        free(tmp);
    }
    free(s);
    s = NULL;
    return;
}

void push_graph_stack(graph_stack_t s, unsigned int vertex){
    graph_list_node_t newnode = make_graph_list_node(vertex);
    newnode->next = s->head;
    s->head = newnode;
    return;
}

int pop_graph_stack(graph_stack_t s, unsigned int* vertex){
    if(s->head != NULL){
        *vertex = s->head->vertex;
        graph_list_node_t tmp = s->head;
        s->head = s->head->next;
        free(tmp);
        return 0;
    }else{
        return -1;
    }
}

void print_graph_stack(graph_stack_t s){
    if(s != NULL){
        print_graph_list_node(s->head);
    }
    return;
}

int is_empty_graph_stack(graph_stack_t s){
    return s->head == NULL;
}

graph_queue_t make_graph_queue(){
    graph_queue_t q = (graph_queue_t) malloc(sizeof(struct queue_graph_struct));
    assert(q != NULL);
    q->head = q->tail = NULL;
    return q;
}

void drop_graph_queue(graph_queue_t q){
    graph_list_node_t tmp = NULL, iter = q->head;
    while(iter){
        tmp = iter;
        iter = iter->next;
        free(tmp);
    }
    free(q);
    q = NULL;
    return;
}

void enqueue_graph_queue(graph_queue_t q, unsigned int vertex ){
    graph_list_node_t newnode = make_graph_list_node(vertex);
    if(q->head == NULL) q->head = q->tail = newnode;
    else{
        q->tail->next = newnode;
        q->tail = newnode;
    }
    return;
}

int dequeue_graph_queue(graph_queue_t q, unsigned int* vertex){
    if(q->head != NULL){
        *vertex = q->head->vertex;
        graph_list_node_t tmp = NULL;
        if(q->head == q->tail){
            tmp = q->head;
            q->head = q->tail = NULL;
            free(tmp);
        }else{
            tmp = q->head;
            q->head = q->head->next;
            free(tmp);
        }
    }else{
        return -1;
    }
}

void print_graph_queue(graph_queue_t q){
    if(q != NULL){
        print_graph_list_node(q->head);
    }
    return;
}

int is_empty_graph_queue(graph_queue_t q){
    return q->head == NULL;
}

int is_white_graph(graph_color_t color){
    return color == WHITE;
}

int is_grey_graph(graph_color_t color){
    return color == GREY;
}

int is_black_graph(graph_color_t color){
    return color == BLACK;
}

void bfs(graph_t G, unsigned int starting_point, unsigned int end_point){
    graph_color_t* color = (graph_color_t*) calloc(G->num_vertices, sizeof(graph_color_t));
    assert(color != NULL);
    path_node_ptr_t reach = (path_node_ptr_t) calloc(G->num_vertices, sizeof(path_node_t));
    assert(reach != NULL);
    for(unsigned int i=0; i<G->num_vertices; i++){
        reach[i].is_reach = UNREACHED;
    }
    graph_queue_t q = make_graph_queue();
    enqueue_graph_queue(q, starting_point);
    reach[starting_point].is_reach = REACHED;
    reach[starting_point].vertex = starting_point;
    reach[starting_point].weight = 0;
    color[starting_point] = GREY;
    unsigned int visited_vertex;
    edge_t iter;
    while(!is_empty_graph_queue(q)){
        dequeue_graph_queue(q, &visited_vertex);
        iter = G->adj_list[visited_vertex];
        while(iter){
            if(is_white_graph(color[iter->dest])){
                enqueue_graph_queue(q, iter->dest);
                color[iter->dest] = GREY;   //mark the vertex as enqueued
                reach[iter->dest].vertex = visited_vertex; //predecessor wich discover the vertex
                reach[iter->dest].weight = reach[visited_vertex].weight + iter->weight;
                reach[iter->dest].is_reach = REACHED; // mark the vertex as reachable for the path
            }
            iter = iter->next;
        }
        color[visited_vertex] = BLACK;
    }
    print_path(reach, starting_point, end_point);
    free(color);
    free(reach);
    drop_graph_queue(q);
    return;
}

void print_path(path_node_ptr_t reach, unsigned int starting_point, unsigned int end_point){
    if(reach[end_point].is_reach == REACHED){
        printf("path: ");
        print_path_helper(reach, starting_point, end_point);
        printf(" total weight: %d\n", reach[end_point].weight);
    }else{
        printf("vertex: %u is unreachable from vertex: %u\n", end_point, starting_point);
    }
    return;
}

void print_path_helper(path_node_ptr_t reach, unsigned int starting_point, unsigned int end_point){
    if(starting_point == end_point){
            printf("%u  ", starting_point);
            return ;
    }else{
        print_path_helper(reach, starting_point, reach[end_point].vertex);
        printf("%u  ", end_point);
        return;
    }
}

void dijkstra(graph_t G, unsigned int starting_point, unsigned int end_point){
    graph_color_t* color = (graph_color_t*) calloc(G->num_vertices, sizeof(graph_color_t));
    assert(color != NULL);
    path_node_ptr_t reach = (path_node_ptr_t) calloc(G->num_vertices, sizeof(path_node_t));
    assert(reach != NULL);
    for(unsigned int i=0; i<G->num_vertices; i++){
        reach[i].is_reach = UNREACHED;
    }
    graph_queue_t q = make_graph_queue();
    enqueue_graph_queue(q, starting_point);
    reach[starting_point].is_reach = REACHED;
    reach[starting_point].vertex = starting_point;
    reach[starting_point].weight = 0;
    color[starting_point] = GREY;
    unsigned int visited_vertex;
    edge_t iter;
    while(!is_empty_graph_queue(q)){
        dequeue_graph_queue(q, &visited_vertex);
        iter = G->adj_list[visited_vertex];
        while(iter){
            if(is_white_graph(color[iter->dest])){
                enqueue_graph_queue(q, iter->dest);
                color[iter->dest] = GREY;   //mark the vertex as enqueued
                reach[iter->dest].vertex = visited_vertex; //predecessor wich discover the vertex
                reach[iter->dest].weight = reach[visited_vertex].weight + iter->weight;
                reach[iter->dest].is_reach = REACHED; // mark the vertex as reachable for the path
            }
            else{
                if(reach[iter->dest].weight > (reach[visited_vertex].weight + iter->weight)){
                    reach[iter->dest].vertex = visited_vertex;
                    reach[iter->dest].weight = reach[visited_vertex].weight + iter->weight;
                }
            }
            iter = iter->next;
        }
        color[visited_vertex] = BLACK;
    }
    print_path(reach, starting_point, end_point);
    free(color);
    free(reach);
    drop_graph_queue(q);
    return;
}

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

void dfs(graph_t G){
    path_node_ptr_t path = (path_node_ptr_t) calloc(G->num_vertices, sizeof(path_node_t));
    assert(path != NULL);
    for(unsigned int i=0; i<G->num_vertices; i++){
        path[i].is_reach = UNREACHED;
    }
    for(unsigned int starting_point = 0; starting_point < G->num_vertices; starting_point++){
        if(path[starting_point].is_reach == UNREACHED){
            path[starting_point].is_reach = REACHED;
            printf("path starting from: ");
            dfs_helper(G, path, starting_point);
            printf("\n");
        }   
    }
    // the array path contains information about the dfs visit
    //the dfs helper prints the visited nodes for simplicity
    free(path);
    return;
}

void dfs_helper(graph_t G, path_node_ptr_t path, unsigned int starting_point){
    printf("%u ", starting_point); 
    for(edge_t iter = G->adj_list[starting_point]; iter != NULL; iter = iter->next){
        if(path[iter->dest].is_reach == UNREACHED){
            path[iter->dest].is_reach = REACHED;
            path[iter->dest].vertex = starting_point;
            path[iter->dest].weight = path[starting_point].weight + iter->weight; 
            dfs_helper(G, path, iter->dest);
        }
    }
    return;
}

graph_stack_t ts(graph_t G){
    path_node_ptr_t reach = (path_node_ptr_t) calloc(G->num_vertices, sizeof(path_node_t));
    assert(reach != NULL);
    graph_stack_t s = make_graph_stack();
    for(unsigned int i=0; i<G->num_vertices; i++){
        reach[i].is_reach = UNREACHED;
    }
    int has_cycle = 0;
    for(unsigned int starting_point = 0; starting_point < G->num_vertices; starting_point++){
        if(reach[starting_point].is_reach == UNREACHED){
            set_true(&has_cycle, ts_dfs(G, reach, starting_point, s));
        }
    }
    if(has_cycle){
        printf("this graph has a cycle, so it haven't a topological order\n");
    }
    printf("ot : ");
    print_graph_list_node(s->head);
    free(reach);
    return s;
}

int ts_dfs(graph_t G, path_node_ptr_t reach, unsigned int starting_point, graph_stack_t s){
    int has_cycle = 0;
    reach[starting_point].is_reach = REACHED_BUT_NOT_LEFT;
    for(edge_t iter = G->adj_list[starting_point]; iter != NULL; iter = iter->next){
        if(reach[iter->dest].is_reach == UNREACHED){
            has_cycle = ts_dfs(G, reach, iter->dest, s);
        }else if(reach[iter->dest].is_reach == REACHED_BUT_NOT_LEFT){
            has_cycle = 1;
        }
    }
    reach[starting_point].is_reach = REACHED;
    push_graph_stack(s, starting_point);
    return has_cycle;
}

void set_true(int* curr, int new_candidate){
    if(new_candidate) *curr = new_candidate;
    return;
}

void scc(graph_t G){
    graph_stack_t s = ts(G);
    path_node_ptr_t reach = (path_node_ptr_t) calloc(G->num_vertices, sizeof(path_node_t));
    assert(reach != NULL);
    int starting_point;
    unsigned int scc_index = 0;
    for(unsigned int i=0; i<G->num_vertices; i++){
        reach[i].is_reach = UNREACHED;
    }
    graph_t gt = transpose(G);
    while(!is_empty_graph_stack(s)){
        pop_graph_stack(s, &starting_point);
        if(reach[starting_point].is_reach == UNREACHED){
            reach[starting_point].is_reach = REACHED;
            printf("scc %u: ", scc_index);
            dfs_helper(gt, reach, starting_point);
            scc_index++;
            printf("\n");
        }
    }
    drop_graph(gt);
    free(reach);
    drop_graph_stack(s);
    return;
}
