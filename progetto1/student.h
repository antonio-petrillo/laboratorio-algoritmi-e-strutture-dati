#ifndef STUDENT_H
#define STUDENT_H 1

typedef struct student_struct{
    char* name;
    char* surname;
    char matricola[10]; //I don't know the english word for this
}* student_t;

student_t make_student(char* name, char* surname, char matricola[]);
void delete_student(student_t s);
void print_student_info(student_t s);
int compare_student(student_t s1, student_t s2);

#endif
