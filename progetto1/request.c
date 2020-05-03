#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "request.h"

loan_list_t make_loan_list(){
    loan_list_t list = (loan_list_t) malloc(sizeof(loan_list_t));
    assert(list != NULL);
    list->head = NULL;
    return list;
}

loan_node_t make_loan_node(student_t student, book_t book){
    loan_node_t newnode = (loan_node_t) malloc(sizeof(struct loan_struct));
    assert(newnode != NULL);
    newnode->book = book;
    newnode->student = student;
    newnode->next = NULL;
    return newnode;
}

void make_a_loan(loan_list_t list, student_t student, book_t book){
    loan_node_t new_loan = make_loan_node(student, book);
    new_loan->next = list->head;
    list->head = new_loan;
    return;
}

loan_node_t return_a_loan(loan_list_t list, student_t student, book_t book){
    assert(list != NULL);
    loan_node_t ret_loan_node = NULL;
    if(list->head != NULL){
        loan_node_t* iter = &(list->head);
        while(compare_ISBN((*iter)->book->ISBN, book->ISBN) && compare_student((*iter)->student, student)){
            iter = &(*iter)->next;
        }
        ret_loan_node = *iter;
        *iter = (*iter)->next;
    }
    else{
        printf("there are no loan associated to this student\n");
    }
    return ret_loan_node;
}

void drop_loan_list(loan_list_t list){
    assert(list != NULL);
    list->head = drop_all_loan_node(list->head);
    free(list);
    list = NULL;
    return;
}

loan_node_t drop_all_loan_node(loan_node_t node){
    if(node){
        node->next = drop_all_loan_node(node->next);
        free(node);
    }
    return NULL;
}

request_queue_t make_request_queue(){
    request_queue_t newqueue = (request_queue_t) malloc(sizeof(request_queue_t));
    assert(newqueue != NULL);
    newqueue->head = newqueue->tail = NULL;
    return newqueue;
}

request_node_t make_request_node(student_t student, book_t book, request_t request){
    request_node_t new_request_node = (request_node_t) malloc(sizeof(request_node_t));
    assert(new_request_node != NULL);
    new_request_node->next = NULL;
    new_request_node->student = student;
    new_request_node->book = book;
    new_request_node->request = request;
    return new_request_node;
}

void enqueue_request(request_queue_t queue, student_t student, book_t book, request_t request){
    request_node_t new_request = make_request_node(student, book, request);
    if(queue->tail == NULL){
        queue->head = queue->tail = new_request;
    }else{
        queue->tail->next = new_request;
        queue->tail = new_request;
    }
    return;
}

request_node_t dequeue_request(request_queue_t queue){
    request_node_t ret_request = NULL;
    if(queue->head != NULL){
        ret_request = queue->head;
        queue->head = queue->head->next;
        if(queue->head == NULL) queue->tail = NULL;
    } 
    return ret_request;
}

void drop_request_queue(request_queue_t queue){
    assert(queue != NULL);
    queue->head = drop_all_queue_node(queue->head);
    queue->head = queue->tail = NULL;
    free(queue);
    queue = NULL;
    return;
}

request_node_t drop_all_queue_node(request_node_t node){
    if(node){
        node->next = drop_all_queue_node(node->next);
        free(node);
    }   
    return NULL;
}

int requests_available(request_queue_t request_queue){
    return request_queue->head != NULL;
}