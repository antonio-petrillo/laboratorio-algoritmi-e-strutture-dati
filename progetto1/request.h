#ifndef REQUEST_H
#define REQUEST_H 1

#include "student.h"
#include "book.h"

typedef enum{GET_BOOK, RETURN_BOOK} request_t;

typedef struct request_queue_struct{
    book_t book;
    student_t student;
    request_t request;
    struct request_queue_struct* next;
}* request_node_t;

typedef struct{
    request_node_t head;
    request_node_t tail;
}* request_queue_t;

typedef struct loan_struct{
    struct loan_struct* next;
    book_t book;
    student_t student;
}* loan_node_t;

typedef struct{
    loan_node_t head;
}* loan_list_t;

loan_list_t make_loan_list();
loan_node_t make_loan_node(student_t student, book_t book);
void make_a_loan(loan_list_t list, student_t student, book_t book);
loan_node_t return_a_loan(loan_list_t list, student_t student, book_t book);
void drop_loan_list(loan_list_t list);
loan_node_t drop_all_loan_node(loan_node_t node);
request_queue_t make_request_queue();
request_node_t make_request_node(student_t student, book_t book, request_t request);
void enqueue_request(request_queue_t queue, student_t student, book_t book, request_t request);
request_node_t dequeue_request(request_queue_t queue);
void drop_request_queue(request_queue_t queue);
request_node_t drop_all_queue_node(request_node_t node);

int requests_available(request_queue_t request_queue);

#endif