#ifndef BOOK_H
#define BOOK_H 1

typedef struct book_struct{
    char ISBN[14];
    char* title;
    unsigned int num_authors;
    char** authors;
    double price;
}* book_t;

book_t make_book(char ISBN[], char* title, unsigned int num_authors, char** authors, double price);
void delete_book(book_t book);

void print_book_info(book_t book);

int compare_by_ISBN(book_t book1, book_t book2);
book_t copy_book(book_t book);

#endif