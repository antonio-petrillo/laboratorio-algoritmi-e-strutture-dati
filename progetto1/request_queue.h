#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H 1

#include "student.h"
#include "book.h"

typedef enum{GET_BOOK, RETURN_BOOK} request_t;

typedef struct request_queue_struct{
    student_t student;
    book_t book;
    request_t request;
    struct request_queue_struct* next;
}* queue_node_t;

typedef struct queue_struct{
    queue_node_t head;
    queue_node_t tail;
}* request_queue;

queue_node_t make_queue_node(student_t student, book_t book, request_t request);
void delete_queue_node(queue_node_t node);
request_queue make_request_queue();
void enqueue_request(request_queue queue, student_t student, book_t book, request_t request);
queue_node_t dequeue_request(request_queue queue);


#endif