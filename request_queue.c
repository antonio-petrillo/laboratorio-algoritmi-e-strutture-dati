#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "request_queue.h"

queue_node_t make_queue_node(student_t student, book_t book, request_t request){
    queue_node_t new_node = (queue_node_t) malloc(sizeof(struct request_queue_struct));
    assert(new_node != NULL);
    new_node->student = student;
    new_node->book = book;
    new_node->request = request; 
    new_node->next = NULL;
    return new_node;
}

void delete_queue_node(queue_node_t node){
    delete_book(node->book);
    delete_student(node->student);
    free(node);
    node = NULL;
    return;
}

request_queue make_request_queue(){
    request_queue q = (request_queue) malloc(sizeof(struct queue_struct));
    assert(q != NULL);
    q->head = q->tail = NULL;
    return q;
}

void enqueue_request(request_queue queue, student_t student, book_t book, request_t request){
    assert(queue != NULL);
    queue_node_t new_node = make_queue_node(student, book, request);
    if(queue->tail == NULL){
        queue->head = queue->tail = new_node;
    }else{
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
    return;
    
}

queue_node_t dequeue_request(request_queue queue){
    assert(queue != NULL);
    queue_node_t ret_node = NULL;
    ret_node = queue->head;
    if(queue->head != NULL){
        if(queue->head == queue->tail){
            queue->head = queue->tail = NULL;
        }
        else{
            queue->head = queue->head->next;
        } 
    }
    return ret_node;
}

void drop_request_queue(request_queue queue){
    assert(queue != NULL);
    queue_node_t tmp;
    while (queue->head){
        tmp = queue->head;
        queue->head = queue->head->next;
        delete_queue_node(tmp);
    }
    free(queue);
    queue = NULL;
    return;
}