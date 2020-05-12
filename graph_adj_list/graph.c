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

graph_stack make_graph_stack(){
    graph_stack s = (graph_stack) malloc(sizeof(struct stack_graph_struct));
    assert(s != NULL);
    s->head = NULL;
    return s;
}


graph_list_node make_graph_list_node(edge_t edge){
    graph_list_node newnode = (graph_list_node) malloc(sizeof(struct list_graph_node_struct));
    assert(newnode != NULL);
    newnode->next = NULL;
    newnode->edge = edge;
    return newnode;
}

void drop_graph_stack(graph_stack s){
    graph_list_node tmp = NULL, iter = s->head;
    while(iter){
        tmp = iter; 
        iter = iter->next;
        free(tmp);
    }
    free(s);
    s = NULL;
    return;
}

void push_graph_stack(graph_stack s, edge_t edge){
    graph_list_node newnode = make_graph_list_node(edge);
    newnode->next = s->head;
    s->head = newnode;
    return;
}

int pop_graph_stack(graph_stack s, edge_t* edge){
    if(s->head != NULL){
        *edge = s->head->edge;
        graph_list_node tmp = s->head;
        s->head = s->head->next;
        free(tmp);
        return 0;
    }else{
        return -1;
    }
}

graph_queue make_graph_queue(){
    graph_queue q = (graph_queue) malloc(sizeof(struct queue_graph_struct));
    assert(q != NULL);
    q->head = q->tail = NULL;
    return q;
}

void drop_graph_queue(graph_queue q){
    graph_list_node tmp = NULL, iter = q->head;
    while(iter){
        tmp = iter;
        iter = iter->next;
        free(tmp);
    }
    free(q);
    q = NULL;
    return;
}

void enqueue_graph_queue(graph_queue q, edge_t edge){
    graph_list_node newnode = make_graph_list_node(edge);
    if(q->head == NULL) q->head = q->tail = newnode;
    else{
        q->tail->next = newnode;
        q->tail = newnode;
    }
    return;
}

int dequeue_graph_queue(graph_queue q, edge_t* edge){
    if(q->head != NULL){
        *edge = q->head->edge;
        graph_list_node tmp = NULL;
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