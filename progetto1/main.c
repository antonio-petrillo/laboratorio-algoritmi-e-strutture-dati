#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "rbtree.h"
#include "request_queue.h"

#define MAX_SIZE 256

#define CREATE_BACKUP 1

void load_library(rbtree tree, char* filename);
void store_library(rbtree tree, char* filename);
void store_library_output(rbtree tree, char* filename);
void store_library_backup(rbtree tree, char* filename);
void store_library_helper(rb_node node, FILE* fp, rb_node lastnode);
void print_library(rbtree tree);
void print_library_helper(rb_node node);
void add_request(rbtree tree, request_queue queue, request_t request, FILE* stream);
void add_loan_request(rbtree tree, request_queue queue, FILE* stream);
void add_return_request(rbtree tree, request_queue queue, FILE* stream);
void handle_request(rbtree tree, request_queue queue);
void handle_single_request(rbtree tree, queue_node_t new_request, request_queue queue);

void print_menu();

int main(int argc, char** argv){
    printf("################### START PROGRAM ###################\n\n");

    if(argc < 2){
        printf("progetto1: missing file operand\nTry ./progetto library.txt\n\n");
        return -1;
    }

    rbtree tree = make_rbtree();
    request_queue queue = make_request_queue();
    load_library(tree, argv[1]);
    printf("################## LIBRARY LOADED ###################\n\n");

    #ifdef CREATE_BACKUP
        printf("################## BACKUP CREATED ###################\n\n");
        store_library_backup(tree, argv[1]);
    #endif
    
    char choice;
    do{
        print_menu();
        printf("choice: ");
        choice = getchar();
        getchar();
        switch (choice){
            case '1':
                add_return_request(tree, queue, stdin);
                puts("");
                break;
            case '2':
                add_loan_request(tree, queue, stdin);
                puts("");
                break;
            case '3':
                handle_request(tree, queue);
                puts("");
                break;
            case '4':
                print_library(tree);
                puts("");
                break;
            case '5':
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    }while(choice != '5');
    store_library_output(tree, argv[1]);
    drop_rbtree(tree);
    drop_request_queue(queue);
    printf("#################### END PROGRAM ####################\n\n");    
    return 0;
}

void load_library(rbtree tree, char* filename){
    FILE* fp = fopen(filename, "r");
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
        rbtree_insert(tree, make_book(ISBN, title, num_authors, authors, price), num_copies);
        authors = NULL;
    } 
    fclose(fp);
    return;
}

void store_library(rbtree tree, char* filename){
    FILE* fp = fopen(filename, "w");
    rb_node lastnode = max_rb(tree);
    store_library_helper(tree->root, fp, lastnode);
    fclose(fp);
    return;
}

void store_library_output(rbtree tree, char* filename){
    unsigned int index = strlen(filename)-1;
    while (filename[index] != '.'){
        index--;
    }
    // + _output.txt + \0 := 12 character
    char* filename_backup = (char*)calloc(index+12, sizeof(char));
    assert(filename_backup != NULL);
    strncpy(filename_backup, filename, index);
    strcat(filename_backup, "_output.txt");
    store_library(tree, filename_backup);
    free(filename_backup);
    return;
}

void store_library_backup(rbtree tree, char* filename){
    unsigned int index = strlen(filename)-1;
    while (filename[index] != '.'){
        index--;
    }
    // + _backup.txt + \0 := 12 character
    char* filename_backup = (char*)calloc(index+12, sizeof(char));
    assert(filename_backup != NULL);
    strncpy(filename_backup, filename, index);
    strcat(filename_backup, "_backup.txt");
    store_library(tree, filename_backup);
    free(filename_backup);
    return;
}

void store_library_helper(rb_node node, FILE* fp, rb_node lastnode){
    if(node){
        fprintf(fp, "%s\n", node->book->ISBN);//isbn
        fprintf(fp, "%s\n", node->book->title);//title
        fprintf(fp, "%u\n", node->book->num_authors);//num_authors
        for(unsigned int i=0; i<node->book->num_authors; i++){
            fprintf(fp, "%s\n", node->book->authors[i]);//authors line by line
        }
        fprintf(fp, "%.2lf\n", node->book->price);
        fprintf(fp, "%u\n", node->num_copies);
        if(node != lastnode) fprintf(fp, "\n");
        store_library_helper(node->left, fp, lastnode);
        store_library_helper(node->right, fp, lastnode);
    }
    return;
}

void print_library(rbtree tree){
    printf("################## LIBRARY CONTENT ##################\n\n");
    print_library_helper(tree->root);
    printf("#####################################################\n\n");
    return;
}

void print_library_helper(rb_node node){
    if(node){
        print_book_info(node->book);
        printf("num copies: %u\n\n", node->num_copies);
        print_library_helper(node->left);
        print_library_helper(node->right);
    }
    return ;
}

void add_request(rbtree tree, request_queue queue, request_t request, FILE* stream){
    char handle_now;
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    char matricola[11];
    char ISBN[15];
    char title[MAX_SIZE];
    unsigned int num_author;
    char num_author_str[MAX_SIZE];
    char** authors;
    char author[MAX_SIZE];
    char price_str[MAX_SIZE];
    double price;
    printf("insert student's name: ");
    fgets(name, MAX_SIZE, stream);
    fflush(stdin);
    name[strlen(name)-1] = '\0';
    printf("insert student's surname: ");
    fgets(surname, MAX_SIZE, stream);
    fflush(stdin);
    surname[strlen(surname)-1] = '\0';
    printf("insert student's matricola (9 char): ");
    fgets(matricola, 11, stream);
    fflush(stdin);
    matricola[strlen(matricola)-1] = '\0';
    printf("insert isbn (max 13 char): ");
    fgets(ISBN, 15, stream);
    fflush(stdin);
    ISBN[strlen(ISBN)-1] = '\0';
    printf("insert title: ");
    fgets(title, MAX_SIZE, stream);
    fflush(stdin);
    title[strlen(title)-1] = '\0';
    printf("insert authors number: ");
    fgets(num_author_str, MAX_SIZE, stream);
    num_author_str[strlen(num_author_str)-1] = '\0';
    num_author = atoi(num_author_str);
    fflush(stdin);
    authors = (char**) calloc(num_author, sizeof(char*));
    assert(author != NULL);
    for(int i=0; i<num_author; i++){
        printf("insert the full name of the %u-ith author: ", (i+1));
        fgets(author, MAX_SIZE, stream);
        fflush(stdin);
        author[strlen(author)-1] = '\0';
        authors[i] = (char*)calloc(strlen(author)+1, sizeof(char));
        assert(authors[i] != NULL);
        strcpy(authors[i], author);
    }
    printf("insert the price of the book: ");
    fgets(price_str, MAX_SIZE, stream);
    price_str[strlen(price_str)-1] = '\0';
    price = atof(price_str);
    fflush(stdin);
    student_t student = make_student(name, surname, matricola);
    book_t book = make_book(ISBN, title, num_author, authors, price);
    printf("\nDo you want to handle the request now? [Y/n]: ");
    handle_now = fgetc(stream);
    fgetc(stream);//remove the '\n' from the buffer
    fflush(stream);
    if(handle_now == 'Y' || handle_now == 'y'){
        queue_node_t tmp_node = make_queue_node(student, book, request);
        handle_single_request(tree, tmp_node, queue);
    }else{
        enqueue_request(queue, student, book, request);
    }
    return;
}

void add_loan_request(rbtree tree, request_queue queue, FILE* stream){
    add_request(tree, queue, GET_BOOK, stream);
    return;
}

void add_return_request(rbtree tree, request_queue queue, FILE* stream){
    add_request(tree, queue, RETURN_BOOK, stream);
    return;
}

void handle_request(rbtree tree, request_queue queue){
    queue_node_t new_request = dequeue_request(queue);
    handle_single_request(tree, new_request, queue);
    return;
}

void handle_single_request(rbtree tree, queue_node_t new_request, request_queue queue){
    if(new_request != NULL){
        if(new_request->request == GET_BOOK){
            book_t book = get_book_from_tree(tree, new_request->book);
            print_student_info_inline(new_request->student);
            printf(", requested requires the book:\n");
            if(book != NULL){
                print_book_info(book);
                puts("");
                delete_book(book);
            }else{
                print_book_info(new_request->book);
                puts("");
                printf("book not present in the library, request suspended\n");
                enqueue_request(queue, copy_student(new_request->student), copy_book(new_request->book), new_request->request);
            }
        }else{// RETURN_BOOK
            print_student_info_inline(new_request->student);
            rb_node tmp = search_rb_node(tree, new_request->book);
            if(tmp){
                printf(", returned the book: \n");
                print_book_info(new_request->book);
                rbtree_insert(tree, new_request->book, 1);
                puts("");
            }else{
                printf(", returned the book:\n");
                print_book_info(new_request->book);
                printf("this book does not belong to this library, request rejected\n");
            }
        }
        delete_queue_node(new_request);
    }
    return;
}

void print_menu(){
    printf("Enter a choice:\n");
    printf("1) Add a return request\n");
    printf("2) Add a loan request\n");
    printf("3) Resume suspended requests\n");
    printf("4) Print library content\n");
    printf("5) End program\n");
    printf("Any other choice will be ignored\n\n");
    return;
}