#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

student_t make_student(char* name, char* surname, char matricola[]){
    student_t new_student = (student_t) malloc(sizeof(struct student_struct));
    assert(new_student != NULL);
    strcpy(new_student->matricola, matricola);
    new_student->name = (char*) calloc(strlen(name)+1, sizeof(char));
    assert(new_student->name);
    strcpy(new_student->name, name);
    new_student->surname = (char*) calloc(strlen(surname)+1, sizeof(char));
    assert(new_student->surname);
    strcpy(new_student->surname, surname);
    return new_student;
}

void delete_student(student_t student){
    if(student){
        free(student->name);
        free(student->surname);
        free(student);
        student = NULL;
    }
    return;
}

student_t copy_student(student_t student){
    return make_student(student->name, student->surname, student->matricola);
}

void print_student_info(student_t student){
    if(student){
        printf("matricola: %s\n", student->matricola);
        printf("name: %s\n", student->name);
        printf("surname: %s\n", student->surname);
    }
    return;
}

void print_student_info_inline(student_t student){
    if(student){
        printf("matricola: %s, ", student->matricola);
        printf("name: %s, ", student->name);
        printf("surname: %s", student->surname);
    }
    return;
}