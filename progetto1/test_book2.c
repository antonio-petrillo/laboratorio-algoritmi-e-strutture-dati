#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "rbtree_library.h"

void printfile(FILE* fp);

int main(int argc, char** argv){
    rbtree library = make_rbtree();
    char** authors1 = (char**) calloc(1, sizeof(char*));
    authors1[0] = (char*) calloc(strlen("Serge Lang")+1, sizeof(char));
    strcpy(authors1[0], "Serge Lang");
    char** authors2 = (char**) calloc(1, sizeof(char*));
    authors2[0] = (char*) calloc(strlen("Barbascura X")+1, sizeof(char));
    strcpy(authors2[0], "Barbascura X");
    book_t book1 = make_book("9788833927015", "La bellezza della matematica", authors1, 1, 14.00);
    book_t book2 = make_book("9788899684693", "Il genio non esiste", authors2, 1, 16.00);
    rbtree_insert(library, book1);
    rbtree_insert(library, book2);
    rbtree_insert(library, book1);
    
    // FILE* fp = fopen(argv[1], "r");
    // printfile(fp);
    in_order_visit_rb(library);
    puts("test prelievo");
    book_t tmp = get_book_from_tree(library, book1);
    in_order_visit_rb(library);
    tmp = get_book_from_tree(library, book1);
    in_order_visit_rb(library);
    tmp = get_book_from_tree(library, book2);
    in_order_visit_rb(library);
    tmp = get_book_from_tree(library, book1);
    in_order_visit_rb(library);
    return 0;
}

void printfile(FILE* fp){
    char str[120];
    while (fgets(str, 119, fp) != NULL)
    {
        printf("%s", str);
    } 
    puts("");
    fclose(fp);
    return;
}