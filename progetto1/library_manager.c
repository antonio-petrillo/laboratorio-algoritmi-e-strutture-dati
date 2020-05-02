#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "library_manager.h"

library_manager_t make_library_manager(char* filename){
    library_manager_t new_library_manager = (library_manager_t) malloc(sizeof(struct library_manager_struct));
    assert(new_library_manager != NULL);
    new_library_manager->filename = (char*) calloc(strlen(filename)+1, sizeof(char));
    assert(new_library_manager->filename != NULL);
    strcpy(new_library_manager->filename, filename);
    new_library_manager->library = make_rbtree();
    assert(new_library_manager->library != NULL);
    return new_library_manager;
}

void load_libray(library_manager_t library_manager){
    FILE* fp = fopen(library_manager->filename, "r");
    assert(fp != NULL);
    load_libray_helper(library_manager->library, fp);
    fclose(fp);
    return;
}

void load_libray_helper(rbtree library, FILE* fp){
    #ifndef MAX_SIZE
    #define MAX_SIZE 256
    #endif
    
    char ISBN[15]; // see below for the isbn size
    char title[MAX_SIZE];
    char str_num_authors[MAX_SIZE];
    unsigned int num_authors;
    char** authors;
    char author[MAX_SIZE];
    char str_price[MAX_SIZE];
    double price;
    char str_num_copies[MAX_SIZE];
    unsigned int num_copies; 
    char flush[2]; // [0]:= '\n' , [1]:= '\0'
    while (!feof(fp)){
        fgets(ISBN, 15, fp);// I need 15 (one more than isbn lenght) characters otherwise it won't read the newline and won't read the title correctly
        ISBN[strlen(ISBN)-1] = '\0';// I also use strlen with isbn because some isbn are shorter than others
        fgets(title, MAX_SIZE, fp);
        title[strlen(title)-1] = '\0';
        fgets(str_num_authors, MAX_SIZE, fp);
        str_num_authors[strlen(str_num_authors)-1] = '\0';
        num_authors = atoi(str_num_authors);
        char** authors = (char**) calloc(num_authors, sizeof(char*));
        assert(authors != NULL);
        for(unsigned int i=0; i<num_authors; i++){
            fgets(author, MAX_SIZE, fp);
            author[strlen(author)-1] = '\0';
            authors[i] = (char*) calloc(strlen(author)+1, sizeof(char));
            assert(authors[i] != NULL);
            strcpy(authors[i], author);
        }
        fgets(str_price, MAX_SIZE, fp);
        str_price[strlen(str_price)-1] = '\0';
        price = atof(str_price);
        fgets(str_num_copies, MAX_SIZE, fp);
        str_num_copies[strlen(str_num_copies)-1] = '\0';
        num_copies = atoi(str_num_copies);
        fgets(flush, 2, fp);
        for(unsigned int i=0; i<num_copies; i++){
            rbtree_insert(library, make_book(ISBN, title, authors, num_authors, price));
        }
        for(unsigned int i=0; i<num_authors; i++){
            free(authors[i]);
        }
        free(authors);
    } 
    #ifdef MAX_SIZE
    #undef MAX_SIZE 
    #endif

    return;
}

void store_library(library_manager_t library_manager);
void create_backup(library_manager_t library_manager);
void delete_library(library_manager_t library_manager);
