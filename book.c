#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

book_t make_book(char ISBN[], char* title, unsigned int num_authors, char** authors, double price){
    book_t new_book = (book_t) malloc(sizeof(struct book_struct));
    assert(new_book != NULL);
    strcpy(new_book->ISBN, ISBN);
    new_book->title = (char*) calloc(strlen(title)+1, sizeof(char));
    assert(new_book->title != NULL);
    strcpy(new_book->title, title);
    new_book->num_authors = num_authors;
    new_book->authors = authors;
    new_book->price = price;
    return new_book;
}

void delete_book(book_t book){
    if(book){
        for(unsigned int i=0; i<book->num_authors; i++){
            free(book->authors[i]);
        }
        free(book->authors);
        free(book->title);
        free(book);
        book = NULL;
    }
    return;
}

void print_book_info(book_t book){
    if(book){
        printf("ISBN: %s\n", book->ISBN);
        printf("title: %s\n", book->title);
        printf("num_author: %u\n", book->num_authors);
        printf("authors:---\n");
        for(unsigned int i=0; i<book->num_authors; i++){
            printf("          |--> %s\n", book->authors[i]);
        }
        printf("price: %lf\n", book->price);
    }
    return;
}

int compare_by_ISBN(book_t book1, book_t book2){
    int i = strcmp(book1->ISBN, book2->ISBN);
    return i == 0 ? 0 : (i > 0 ? 1 : -1);
}

book_t copy_book(book_t book){
    assert(book != NULL);
    char** authors = (char**) calloc(book->num_authors, sizeof(char*));
    assert(authors != NULL);
    for(unsigned int i=0; i<book->num_authors; i++){
        authors[i] = (char*) calloc(strlen(book->authors[i])+1, sizeof(char));
        assert(authors[i] != NULL);
        strcpy(authors[i], book->authors[i]);
    }
    return make_book(book->ISBN, book->title, book->num_authors, authors, book->price);
}