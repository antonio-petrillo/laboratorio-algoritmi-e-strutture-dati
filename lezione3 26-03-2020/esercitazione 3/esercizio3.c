#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    struct node* next;
    char name[20];
    char surname[20];
    unsigned int age; 
}Node;

typedef Node* NodePtr;
typedef NodePtr List;

NodePtr makenode(char* name, char* surname, unsigned int age);
List insert(List L, NodePtr node);
void print(const List L);
List drop_list(List L);

List rimuovi_minorenni(List L);

int main(int argc, char** argv){
    List L = NULL;
    FILE* fp = fopen(argv[1], "r");
    unsigned int age;
    char buffer_name[20];
    char buffer_surname[20];
    while(fscanf(fp, "%u%s%s", &age, buffer_name, buffer_surname) > 0) L = insert(L, makenode(buffer_name, buffer_surname, age));
    print(L);
    printf("rimozione degli elementi\n\n");
    L = rimuovi_minorenni(L);
    print(L);
    L = drop_list(L);
    fclose(fp);
    return 0;
}

NodePtr makenode(char* name, char* surname, unsigned int age){
    NodePtr newnode = (NodePtr)malloc(sizeof(Node));
    if(!newnode){fprintf(stderr, "errore\n"); exit(1);}
    newnode->next = NULL;
    newnode->age = age;
    strcpy(newnode->name, name);
    strcpy(newnode->surname, surname);
    return newnode;
}

List insert(List L, NodePtr node){
    node->next = L;
    return node;
}

void print(const List L){
    if(!L) return;
    printf("nome:%s\ncognome:%s\neta':%u\n\n", L->name, L->surname, L->age);
    print(L->next);
    return;
}

List drop_list(List L){
    if(!L) return L;
    L->next = drop_list(L->next);
    free(L);
    return NULL;
}

//esercizio
List rimuovi_minorenni(List L){
    if(!L) return NULL;
    L->next = rimuovi_minorenni(L->next);
    NodePtr tmp = NULL;
    if(L->age < 18){
        tmp = L;
        L = L->next;
        free(tmp);
    }
    return L;
}