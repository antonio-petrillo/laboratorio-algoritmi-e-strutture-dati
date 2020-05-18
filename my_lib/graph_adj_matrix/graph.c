#include "graph.h"

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
		add_edge(g, weight, dest, src);
	}
	return g;

    /*
    first line: --> num_vertices
    loop: first:  --> src
          second: --> sdest
          third:  --> weight
    */
}

graph_t make_empty_graph(size_t num_vertices){
    graph_t g = (graph_t) malloc(sizeof(struct graph_struct));
    assert(g != NULL);
    g->num_vertices = num_vertices;
    g->adj_matrix = (int**) calloc(num_vertices*num_vertices, sizeof(int*));
    for(size_t i=0; i<g->num_vertices; i++){
        g->adj_matrix[i] = (int*) calloc(g->num_vertices, sizeof(int));
        assert(g->adj_matrix[i]!=NULL);
    }
    assert(g->adj_matrix != NULL);
    return g;
}

void drop_graph(graph_t g){
    assert(g != NULL);
    if(g != NULL){
        free(g->adj_matrix);
        free(g);
        g = NULL;
    }
    return;
}

void print_graph(graph_t g){
    assert(g != NULL);
    int to_print;
    for(size_t i=0; i < g->num_vertices; i++){
        printf("ADJ OF %lu: ", i);
        for(size_t j=0; j < g->num_vertices; j++){
            if(to_print = g->adj_matrix[i][j], to_print != 0){
                printf("(dest: %lu, weight: %d)", j,  to_print);
            }
        }    
        printf(" --/\n");
    }
    return;
}

void print_full_graph_matrix(graph_t g){
    assert(g != NULL);
    printf("ADJ MATRIX: \n");
    printf("         ");
    for(size_t i=0; i < g->num_vertices; i++){
        printf("  col[%2lu] ", i);
    }
    printf("\n");
    for(size_t i=0; i < g->num_vertices; i++){
        printf("raw[%2lu]", i);
        for(size_t j=0; j < g->num_vertices; j++){
            printf("%9d ", g->adj_matrix[i][j]);
        }
        printf("\n");
    }
    return;
}

void add_vertex(graph_t g){
    assert(g != NULL);
    g->num_vertices;
    int** new_m = (int**) calloc(g->num_vertices+1, sizeof(int**));
    assert(new_m != NULL);
    for(size_t i=0; i<g->num_vertices+1; i++){
        new_m[i] = (int*) calloc(g->num_vertices+1, sizeof(int));
        assert(new_m != NULL);
        for(size_t j=0; j<g->num_vertices && i!=g->num_vertices; j++){
            new_m[i][j] = g->adj_matrix[i][j];
        }
        if(i!=g->num_vertices) free(g->adj_matrix[i]);
    }
    g->num_vertices++;
    free(g->adj_matrix);
    g->adj_matrix = new_m;
    return;
}

void remove_vertex(graph_t g, size_t v){
    assert(g != NULL);
    int** new_m = (int**) calloc(g->num_vertices-1, sizeof(int*));
    assert(new_m != NULL);
    size_t i_offeset = 0, j_offset = 0;
    for(size_t i=0; i<g->num_vertices; i++){
        j_offset = 0;
        if(i == v){
            free(g->adj_matrix[v]);
            i_offeset = 1;
            continue;
        } 
        new_m[i-i_offeset] = (int*) calloc(g->num_vertices-1, sizeof(int));
        assert(new_m[i-i_offeset] != NULL);
        for(size_t j=0; j<g->num_vertices; j++){
            if(j == v){
                j_offset = 1;
                continue;
            }
            new_m[i-i_offeset][j-j_offset] = g->adj_matrix[i][j];
        }
        free(g->adj_matrix[i]);
    }
    g->num_vertices--;
    free(g->adj_matrix);
    g->adj_matrix = new_m;
    return;
}

void add_edge(graph_t g, int weight, size_t dest, size_t src){
    assert(g != NULL);
    g->adj_matrix[src][dest] = weight;  
    return;
}

void remove_edge(graph_t g, size_t dest, size_t src){
    assert(g != NULL);
    g->adj_matrix[src][dest] = 0;
    return;
}

graph_t transpose(graph_t g){
    graph_t gt = make_empty_graph(g->num_vertices);
    assert(gt != NULL);
    for(size_t i=0; i < g->num_vertices; i++){
        for(size_t j=0; j < g->num_vertices; j++){
            gt->adj_matrix[j][i] = g->adj_matrix[i][j];
        }
    }
    return gt;
}

graph_stack_t make_graph_stack(){
    graph_stack_t s = (graph_stack_t) malloc(sizeof(struct stack_graph_struct));
    assert(s != NULL);
    s->head = NULL;
    return s;
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

graph_list_node_t make_graph_list_node(size_t vertex){
    graph_list_node_t newnode = (graph_list_node_t) malloc(sizeof(struct list_graph_node_struct));
    assert(newnode != NULL);
    newnode->next = NULL;
    newnode->vertex = vertex;
    return newnode;
}

void print_graph_list_node(graph_list_node_t n){
    if(n){
        printf(" %lu", n->vertex);
        print_graph_list_node(n->next);
    }
    else{
        printf("\n");
    }
    return;
}

void push_graph_stack(graph_stack_t s, size_t vertex){
    graph_list_node_t newnode = make_graph_list_node(vertex);
    newnode->next = s->head;
    s->head = newnode;
    return;
}

int pop_graph_stack(graph_stack_t s, size_t* vertex){
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

void enqueue_graph_queue(graph_queue_t q, size_t vertex ){
    graph_list_node_t newnode = make_graph_list_node(vertex);
    if(q->head == NULL) q->head = q->tail = newnode;
    else{
        q->tail->next = newnode;
        q->tail = newnode;
    }
    return;
}

int dequeue_graph_queue(graph_queue_t q, size_t* vertex){
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

int is_empty_graph_queue(graph_queue_t q){
    return q->head == NULL;
}

void bfs(graph_t g, size_t end_point, size_t starting_point){
    assert(g != NULL);
    graph_queue_t q = make_graph_queue();
    enqueue_graph_queue(q, starting_point);
    path_node_ptr_t path = (path_node_ptr_t) calloc(g->num_vertices, sizeof(path_node_t));
    assert(path != NULL);
    for(size_t i=0; i<g->num_vertices; i++){
        path[i].is_reach = UNREACHED;
    }
    path[starting_point].is_reach = REACHED;
    path[starting_point].vertex = starting_point;
    path[starting_point].weight = 0;
    size_t visited_vertex = 0;
    while(!is_empty_graph_queue(q)){
        dequeue_graph_queue(q, &visited_vertex);
        for(size_t i=0; i<g->num_vertices; i++){
            if(g->adj_matrix[visited_vertex][i] != 0 && path[i].is_reach == UNREACHED){
                path[i].is_reach = REACHED;
                path[i].vertex = visited_vertex;
                path[i].weight = path[visited_vertex].weight + g->adj_matrix[visited_vertex][i];
                enqueue_graph_queue(q, i);
            }
        }
    }
    print_path(path, starting_point, end_point);
    free(path);
    drop_graph_queue(q);
    return;
}

void dijkstra(graph_t g, size_t end_point, size_t starting_point){
    assert(g != NULL);
    graph_queue_t q = make_graph_queue();
    enqueue_graph_queue(q, starting_point);
    path_node_ptr_t path = (path_node_ptr_t) calloc(g->num_vertices, sizeof(path_node_t));
    assert(path != NULL);
    for(size_t i=0; i<g->num_vertices; i++){
        path[i].is_reach = UNREACHED;
    }
    path[starting_point].is_reach = REACHED;
    path[starting_point].vertex = starting_point;
    path[starting_point].weight = 0;
    size_t visited_vertex = 0;
    while(!is_empty_graph_queue(q)){
        dequeue_graph_queue(q, &visited_vertex);
        for(size_t i=0; i<g->num_vertices; i++){
            if(g->adj_matrix[visited_vertex][i] != 0 && path[i].is_reach == UNREACHED){
                path[i].is_reach = REACHED;
                path[i].vertex = visited_vertex;
                path[i].weight = path[visited_vertex].weight + g->adj_matrix[visited_vertex][i];
                enqueue_graph_queue(q, i);
            }
            else {
                if(g->adj_matrix[visited_vertex][i] != 0 && path[i].weight > path[visited_vertex].weight + g->adj_matrix[visited_vertex][i]){
                    path[i].weight = path[visited_vertex].weight + g->adj_matrix[visited_vertex][i];
                    path[i].vertex = visited_vertex;
                }
            }
        }
    }
    print_path(path, starting_point, end_point);
    free(path);
    drop_graph_queue(q);
    return;   
}

void print_path(path_node_ptr_t reach, size_t starting_point, size_t end_point){
    if(reach[end_point].is_reach == REACHED){
        printf("path: ");
        print_path_helper(reach, starting_point, end_point);
        printf(" total weight: %d\n", reach[end_point].weight);
    }else{
        printf("vertex: %lu is unreachable from vertex: %lu\n", end_point, starting_point);
    }
    return;
}

void print_path_helper(path_node_ptr_t reach, size_t starting_point, size_t end_point){
    if(starting_point == end_point){
            printf("%lu  ", starting_point);
            return ;
    }else{
        print_path_helper(reach, starting_point, reach[end_point].vertex);
        printf("%lu  ", end_point);
        return;
    }
}

void dfs(graph_t g){
    assert(g != NULL);
    path_node_ptr_t path = (path_node_ptr_t) calloc(g->num_vertices, sizeof(path_node_t));
    assert(path != NULL);
    for(size_t i=0; i<g->num_vertices; i++){
        path[i].is_reach = UNREACHED;
    }
    for(size_t i=0; i<g->num_vertices; i++){
        if(path[i].is_reach == UNREACHED){
            path[i].is_reach = REACHED;
            printf("dfs path: ");
            dfs_helper(g, path, i);
            printf("\n");
        }
    }
    free(path);
    return;
}

void dfs_helper(graph_t g, path_node_ptr_t path, size_t starting_point){
    printf("%lu ", starting_point);
    for(size_t i=0; i<g->num_vertices; i++){
        if(g->adj_matrix[starting_point][i] != 0 && path[i].is_reach == UNREACHED){
            path[i].is_reach = REACHED;
            path[i].vertex = starting_point;
            path[i].weight = path[starting_point].weight + g->adj_matrix[starting_point][i];
            dfs_helper(g, path, i);
        }
    }
    return;
}

graph_stack_t ts(graph_t g){
    assert(g != NULL);
    path_node_ptr_t reach = (path_node_ptr_t) calloc(g->num_vertices, sizeof(path_node_t));
    assert(reach != NULL);
    graph_stack_t s = make_graph_stack();
    for(unsigned int i=0; i<g->num_vertices; i++){
        reach[i].is_reach = UNREACHED;
    }
    int has_cycle = 0;
    for(unsigned int starting_point = 0; starting_point < g->num_vertices; starting_point++){
        if(reach[starting_point].is_reach == UNREACHED){
            set_true(&has_cycle, ts_dfs(g, reach, starting_point, s));
        }
    }
    if(has_cycle){
        printf("this graph has a cycle, so it haven't a topological order\n");
    }else{
        printf("ot : ");
        print_graph_list_node(s->head);
    }
    free(reach);
    return s;
}

int ts_dfs(graph_t g, path_node_ptr_t reach, size_t starting_point, graph_stack_t s){
    int has_cycle = 0;
    reach[starting_point].is_reach = REACHED_BUT_NOT_LEFT;
    for(size_t i=0; i<g->num_vertices; i++){
        if(g->adj_matrix[starting_point][i] != 0){
            if(reach[i].is_reach == UNREACHED){
                has_cycle = ts_dfs(g, reach, i, s);
            }else if(reach[i].is_reach == REACHED_BUT_NOT_LEFT){
                has_cycle = 1;
            }
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

void scc(graph_t g){
    assert(g != NULL);
    graph_stack_t s = ts(g);
    path_node_ptr_t reach = (path_node_ptr_t) calloc(g->num_vertices, sizeof(path_node_t));
    assert(reach != NULL);
    size_t starting_point;
    size_t scc_index = 0;
    for(size_t i=0; i<g->num_vertices; i++){
        reach[i].is_reach = UNREACHED;
    }
    graph_t gt = transpose(g);
    while(!is_empty_graph_stack(s)){
        pop_graph_stack(s, &starting_point);
        if(reach[starting_point].is_reach == UNREACHED){
            reach[starting_point].is_reach = REACHED;
            printf("scc %lu: ", scc_index);
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