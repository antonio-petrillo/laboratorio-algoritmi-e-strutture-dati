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
    strcpy(new_library_manager->loan_filename, "loan_list.txt");
    strcpy(new_library_manager->loan_filename, "request_queue.txt");
    new_library_manager->library = make_rbtree();
    new_library_manager->loan_list = make_loan_list();
    new_library_manager->request_queue = make_request_queue();
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

void store_library(library_manager_t library_manager){
	assert(library_manager != NULL);
	if(!is_empty_rb(library_manager->library)){
		FILE* fp = fopen(library_manager->filename, "w");
		assert(fp != NULL);
		store_library_helper(library_manager->library->root, fp);
		fclose(fp);
	}
	return;
}

void store_library_helper(rb_node node, FILE* fp){
	assert(fp != NULL);
	if(node != NULL){
		fprintf(fp, "%s\n", node->node_info->ISBN);//isbn
        fprintf(fp, "%s\n", node->node_info->title);//title
        fprintf(fp, "%u\n", node->node_info->num_authors);// book's author (number)
        for(int i=0;  i<node->node_info->num_authors; i++){
            fprintf(fp, "%s\n", node->node_info->authors[i]);// author
        }
        fprintf(fp, "%.2lf\n", node->node_info->price);//price
        fprintf(fp, "%u\n", booklist_size(node->booklist));
        fprintf(fp, "\n");
        store_library_helper(node->left, fp);
        store_library_helper(node->right, fp);
    }
	return;
}

void create_backup(library_manager_t library_manager){
	assert(library_manager != NULL);
	//_backup.txt : 11 character + 1 for the \0 = +12
	unsigned int len = strlen(library_manager->filename) - 1;
	while(library_manager->filename[len] != '.'){//string lenght without the extension
		len--;
	}
	char* backup_filename = (char*) calloc(len + 12, sizeof(char));
	assert(backup_filename);
	while(library_manager->filename[len] != '.'){
		len--;
	}
	strncpy(backup_filename, library_manager->filename, len);
	strcat(backup_filename, "_backup.txt");
	FILE* fp = fopen(backup_filename, "w");
	assert(fp != NULL);
	store_library_helper(library_manager->library->root, fp);
	fclose(fp);
	free(backup_filename);
	return;
}

void delete_library(library_manager_t library_manager){
	if(library_manager){
		drop_rbtree(library_manager->library);
        drop_loan_list(library_manager->loan_list);
        drop_request_queue(library_manager->request_queue);
		free(library_manager->filename);
        free(library_manager);
	}
	return;
}

//RBM: 0 --> GET_BOOK, 1 --> RETURN_BOOK
void load_request(library_manager_t library_manager){
    FILE* fp = fopen(library_manager->request_filename, "r");
    
    #ifndef MAX_SIZE
    #define MAX_SIZE 256
    #endif
    
    char student_name[MAX_SIZE];
    char student_surname[MAX_SIZE];
    char matricola[11]; //same as isbn
    char str_request[3];
    request_t request;
    char ISBN[15]; // see below for the isbn size
    char title[MAX_SIZE];
    char str_num_authors[MAX_SIZE];
    unsigned int num_authors;
    char** authors;
    char author[MAX_SIZE];
    char str_price[MAX_SIZE];
    double price;
    
    char flush[2]; // [0]:= '\n' , [1]:= '\0'
    while (!feof(fp)){
        fgets(student_name, MAX_SIZE, fp);
        student_name[strlen(student_name)-1] = '\0';
        fgets(student_surname, MAX_SIZE, fp);
        student_surname[strlen(student_surname)-1] = '\0';
        fgets(matricola, 11, fp);
        matricola[strlen(matricola)-1] = '\0';
        fgets(str_request, 3, fp);
        str_request[strlen(str_request)-1] = '\0';
        request = atoi(str_request);
        fgets(ISBN, 15, fp);// I need 15 (one more than isbn length) characters otherwise it won't read the newline and won't read the title correctly
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
        fgets(flush, 2, fp);
        enqueue_request(library_manager->request_queue, make_student(student_name, student_surname, matricola), make_book(ISBN, title, authors, num_authors, price), request);
        // the order of the request queue is the same as file 
        for(unsigned int i=0; i<num_authors; i++){
            free(authors[i]);
        }
        free(authors);
    } 
    #ifdef MAX_SIZE
    #undef MAX_SIZE 
    #endif

    fclose(fp);
    return;    
}

void store_request(library_manager_t library_manager){
    FILE* fp = fopen(library_manager->request_filename, "w");
    assert(fp != NULL);
    request_node_t iter = library_manager->request_queue->head;
    while(iter != NULL){
        fprintf(fp, "%s\n", iter->student->name);
        fprintf(fp, "%s\n", iter->student->surname);
        fprintf(fp, "%s\n", iter->student->matricola);
        fprintf(fp, "%d\n", iter->request);
        fprintf(fp, "%s\n", iter->book->ISBN);//isbn
        fprintf(fp, "%s\n", iter->book->title);//title
        fprintf(fp, "%u\n", iter->book->num_authors);// book's author (number)
        for(int i=0;  i<iter->book->num_authors; i++){
            fprintf(fp, "%s\n", iter->book->authors[i]);// author
        }
        fprintf(fp, "%.2lf\n", iter->book->price);//price
        fprintf(fp, "\n");
        iter = iter->next;
    }
    fclose(fp);
}

void load_loan_list(library_manager_t library_manager){
    FILE* fp = fopen(library_manager->loan_filename, "r");
    assert(fp != NULL);
    #ifndef MAX_SIZE
    #define MAX_SIZE 256
    #endif
    char student_name[MAX_SIZE];
    char student_surname[MAX_SIZE];
    char matricola[11]; //same as isbn
    char ISBN[15]; // see below for the isbn size
    char title[MAX_SIZE];
    char str_num_authors[MAX_SIZE];
    unsigned int num_authors;
    char** authors;
    char author[MAX_SIZE];
    char str_price[MAX_SIZE];
    double price;
    char flush[2]; // [0]:= '\n' , [1]:= '\0'
    while (!feof(fp)){
        fgets(student_name, MAX_SIZE, fp);
        student_name[strlen(student_name)-1] = '\0';
        fgets(student_surname, MAX_SIZE, fp);
        student_surname[strlen(student_surname)-1] = '\0';
        fgets(matricola, 11, fp);
        matricola[strlen(matricola)-1] = '\0';
        fgets(ISBN, 15, fp);// I need 15 (one more than isbn length) characters otherwise it won't read the newline and won't read the title correctly
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
        fgets(flush, 2, fp);
        make_a_loan(library_manager->loan_list, make_student(student_name, student_surname, matricola), make_book(ISBN, title, authors, num_authors, price));
        for(unsigned int i=0; i<num_authors; i++){
            free(authors[i]);
        }
        free(authors);
    } 
    #ifdef MAX_SIZE
    #undef MAX_SIZE 
    #endif

    fclose(fp);
}

void store_loan_list(library_manager_t library_manager){
    FILE* fp = fopen(library_manager->loan_filename, "w");
    assert(fp != NULL);
    loan_node_t iter = library_manager->loan_list->head;
    while(iter != NULL){
        fprintf(fp, "%s\n", iter->student->name);
        fprintf(fp, "%s\n", iter->student->surname);
        fprintf(fp, "%s\n", iter->student->matricola);
        fprintf(fp, "%s\n", iter->book->ISBN);//isbn
        fprintf(fp, "%s\n", iter->book->title);//title
        fprintf(fp, "%u\n", iter->book->num_authors);// book's author (number)
        for(int i=0;  i<iter->book->num_authors; i++){
            fprintf(fp, "%s\n", iter->book->authors[i]);// author
        }
        fprintf(fp, "%.2lf\n", iter->book->price);//price
        fprintf(fp, "\n");
        iter = iter->next;
    }
    fclose(fp);
    return;
}

void handle_library_request(library_manager_t library_manager){
    request_node_t new_request = NULL;
    book_t book = NULL;
    loan_node_t new_return = NULL;
    while (requests_available(library_manager->request_queue)){
        new_request = dequeue_request(library_manager->request_queue);
        if(new_request->request == GET_BOOK){
            printf("matricola:%s requeriers a book %s\n", new_request->student->matricola, new_request->book->ISBN);
            book = get_book_from_tree(library_manager->library, new_request->book);
            if(book){
                make_a_loan(library_manager->loan_list, new_request->student, book);
                printf("loan made!\n");
            }else{
                printf("impossible to make the loan\n");
                free(new_request->book);
                free(new_request->student);
            }
        }
        else{//RETURN BOOK
            new_return = return_a_loan(library_manager->loan_list, new_request->student, new_request->book);
            if(new_return != NULL){
                printf("matricola: %s returned the book: %s\n", new_return->student->matricola, new_return->book->ISBN);
                rbtree_insert(library_manager->library, new_request->book);
                
            }else{
                free(new_request->book);
                printf("nothing to do \nthere are no loans made out to matricola:%s\n", new_request->student->matricola);
            }
            free(new_request->student);
        }
        free(new_request);
        new_request = NULL;

        #ifdef STEP_BY_STEP
            printf("press any key to continue...\n");
            getchart();
        #endif

    }
    printf("there are no more requests to handle\n");
    return;
}