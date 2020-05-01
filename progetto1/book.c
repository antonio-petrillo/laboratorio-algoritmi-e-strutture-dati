#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "book.h"


book_t make_book(char ISBN[], char* title, char** authors, unsigned int num_authors, double price){
    book_t new_book = (book_t) malloc(sizeof(struct book_struct));
    assert(new_book != NULL);
    assert(num_authors > 0);
    new_book->num_authors = num_authors;
    new_book->price = price;
    strcpy(new_book->ISBN, ISBN);    
    new_book->title = (char*) calloc(strlen(title)+1, sizeof(char));
    assert(new_book->title != NULL);
    strcpy(new_book->title, title); 
    new_book->authors = (char**) calloc(num_authors, sizeof(char*));
    assert(new_book->authors != NULL);
    for(unsigned int i=0; i<num_authors; i++){
        new_book->authors[i] = (char*) calloc(strlen(authors[i])+1, sizeof(char));
        assert(new_book->authors[i] != NULL);
        strcpy(new_book->authors[i], authors[i]);
    }
    return new_book;
}

book_t delete_book(book_t book){
    for(unsigned int i=0; i<book->num_authors; i++){
        free(book->authors[i]);
    }
    free(book->authors);
    free(book->title);
    free(book);
    book = NULL;
    return book;
}

void print_book_info(book_t book){
    if(book){
        printf("########### BOOK INFO ##############\n");
        printf("TITLE: %s\n", book->title);
        printf("ISBN: %s\n", book->ISBN);
        printf("%s:--%s\n", ((book->num_authors == 1) ? "AUTHOR" : "AUTHORS"), book->authors[0]);
        for(unsigned int i=1; i < book->num_authors; i++){
            printf("        |-%s\n", book->authors[i]);
        }
        printf("PRICE: %.2lf\n", book->price);
        printf("####################################\n\n");
    }
    return;
}

booknode_t make_booknode(book_t book){
    booknode_t newnode =  (booknode_t) malloc(sizeof(struct booknode_struct));
    assert(newnode != NULL);
    newnode->book = book;
    newnode->next = NULL;
    return newnode;
}

booklist_t make_booklist(){
    booklist_t new_booklist = (booklist_t) malloc(sizeof(struct booklist_struct));
    assert(new_booklist != NULL);
    new_booklist->head = NULL;
    return new_booklist;
}

void booklist_push(booklist_t booklist, book_t book){
    booknode_t new_booknode = make_booknode(book);
    new_booknode->next = booklist->head;
    booklist->head = new_booknode;
    return;
}

book_t booklist_pop(booklist_t booklist){
    booknode_t tmp = booklist->head;
    book_t ret_value = (tmp != NULL) ? tmp->book : NULL;
    if(booklist->head){
        booklist->head = booklist->head->next; 
    }
    free(tmp);
    return ret_value;
}

void drop_booklist(booklist_t booklist){
    if(booklist->head){
        booklist->head = drop_all_booknode(booklist->head);
    }
    free(booklist);
    booklist = NULL;
    return;
}

booknode_t drop_all_booknode(booknode_t booknode){
    if(booknode){
        booknode->next = drop_all_booknode(booknode->next);
        free(booknode);
    }
    return NULL;
}

int compare_ISBN(char* ISBN1, char* ISBN2){
    int res = strcmp(ISBN1, ISBN2);
    return (res > 0) ? 1 : ((res < 0) ? -1 : 0);
}

void print_booklist(booklist_t booklist){
    booknode_t iter = booklist->head;
    while(iter){
        print_book_info(iter->book);
        iter = iter->next;
    }
    return;
}

unsigned int booklist_size(booklist_t booklist){
    unsigned int size = 0;
    booknode_t iter = booklist->head;
    while(iter){
        iter = iter->next;
        size++;
    }
    return size;
}

void copy_booklist(booklist_t dest, booklist_t src){
    booknode_t iter = src->head;
    while(iter){
        booklist_push(dest, iter->book);
        iter = iter->next;
    }
    return;
}