#ifndef BOOK_H
#define BOOK_H 1

typedef struct book_struct{
    char ISBN[14];
    char* title;
    char** authors;
    unsigned int num_authors;
    double price;
}* book_t;

book_t make_book(char ISBN[], char* title, char** authors, unsigned int num_authors, double price);
book_t copy_book(book_t book);
book_t delete_book(book_t book);
void print_book_info(book_t book);

typedef struct booknode_struct{
    book_t book;
    struct booknode_struct* next;
}* booknode_t;

typedef struct booklist_struct{
    booknode_t head;
}* booklist_t;

booknode_t make_booknode(book_t book);
booklist_t make_booklist();
void booklist_push(booklist_t booklist, book_t book);
book_t booklist_pop(booklist_t booklist);
void drop_booklist(booklist_t booklist);
booknode_t drop_all_booknode(booknode_t booknode);
int compare_ISBN(char* ISBN1, char* ISBN2);

void print_booklist(booklist_t booklist);
unsigned int booklist_size(booklist_t booklist);
void copy_booklist(booklist_t dest, booklist_t src);

#endif