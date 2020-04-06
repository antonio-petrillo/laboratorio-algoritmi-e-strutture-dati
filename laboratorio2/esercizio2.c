#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char* name;
    struct node* next;
    struct node* prev;
}Node;

typedef Node* NodePtr;
typedef NodePtr List;

List makelist();
NodePtr makenode(char name[]);
List insert(List L, char name[]);
List drop(List L);
void print(List L);

int main(int argc, char** argv){
    FILE* fp = fopen(argv[1], "r");
    if(!fp) exit(1);
    char buffer[256];
    List l = makelist();
    while(fscanf(fp, "%s", buffer) > 0) l = insert(l, buffer);
    printf("stampa della lista\n");
    print(l);
    fclose(fp);
    return 0;
}

List makelist(){
    return NULL;
}

NodePtr makenode(char name[]){
    NodePtr newnode = (NodePtr) malloc(sizeof(Node));
    if(!newnode){
        fprintf(stderr, "impossibile allocare un nuovo nodo\n");
        exit(1);
    }
    newnode->next = newnode->prev = NULL;
    newnode->name = (char*)calloc(strlen(name)+1, sizeof(char));
    if(!newnode->name){
        fprintf(stderr, "impossibile allocare un nuovo nodo\n");
        exit(1);
    }
    strcpy(newnode->name, name);
    return newnode;
}

List insert(List L, char name[]){
    if(!L) return makenode(name);
    else{
        if(strcmp(name, L->name) >  0){
            L->next = insert(L->next, name);
            return L;
        }else{
            NodePtr newnode = makenode(name);
            newnode->next = L;
            if(L->prev){
                newnode->prev = L->prev;
                L->prev->next = newnode;
            }
            L->prev = newnode;
            return newnode;
        }
    }
}

List drop(List L){
    if(!L) return NULL;
    L->next = drop(L->next);
    free(L);
    return NULL;
}

void print(List L){
    if(!L) return;
    printf("valore del nodo := %s\n", L->name);
    print(L->next);
    return;
}