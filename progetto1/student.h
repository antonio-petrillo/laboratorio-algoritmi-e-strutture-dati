#ifndef STUDENT_H
#define STUDENT_H 1

    typedef struct student_struct{
        char* name;
        char* surname;
        char matricola[10];//I don't know the english word for matricola
    }* student_t;
    
    student_t make_student(char* name, char* surname, char matricola[]);
    void delete_student(student_t student);
    student_t copy_student(student_t student);
    void print_student_info(student_t student);
    void print_student_info_inline(student_t student);

#endif