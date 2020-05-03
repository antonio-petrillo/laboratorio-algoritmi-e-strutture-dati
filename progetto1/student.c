#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "student.h"

student_t make_student(char* name, char* surname, char matricola[]){
    student_t new_student = (student_t) malloc(sizeof(struct student_struct));
    assert(new_student != NULL);
    new_student->name = (char*) calloc(strlen(name)+1, sizeof(char));
    assert(new_student->name != NULL);
    new_student->surname = (char*) calloc(strlen(surname)+1, sizeof(char));
    assert(new_student->surname != NULL);
    strcpy(new_student->name, name);
    strcpy(new_student->surname, surname);
    strcpy(new_student->matricola, matricola);
    return new_student;
}

void delete_student(student_t s){
    assert(s);
    free(s->name);
    free(s->surname);
    free(s);
    s = NULL;
    return ;
}

void print_student_info(student_t s){
    if(s){
        printf("################# STUDENT'S INFO #################\n\n");
        printf("matricola: %s\n", s->matricola);
        printf("nome: %s\n", s->name);
        printf("cognome: %s\n\n", s->surname);
        printf("#################################################\n\n");
    }
    else{
        printf("UNRECOGNIZED STUDENT\n");
    }
    return;
}

int compare_student(student_t s1, student_t s2){
    assert(s1 != NULL && s2 != NULL);
    return strcmp(s1->matricola, s2->matricola);
}