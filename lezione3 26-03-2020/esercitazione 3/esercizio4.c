#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    double x;
    double y;
    double z;
    struct node* next;
}Node;

typedef Node* NodePtr;
typedef NodePtr List;

NodePtr makenode(double x, double y, double z);
List insert(List L, NodePtr node);
void print(const List L);
List drop_list(List L);

void calcola_espressione(const List L);
void calcola_espressione_rec(const List L, NodePtr res);

int main(int argc, char** argv){
        List L = NULL;
    FILE* fp = fopen(argv[1], "r");
    double x, y, z;
    while(fscanf(fp, "%lf%lf%lf", &x, &y, &z) > 0) L = insert(L, makenode(x, y, z));
    print(L);
    printf("calcolo dell'espressione\n\n");
    calcola_espressione(L);
    L = drop_list(L);
    fclose(fp);
    return 0;
}

NodePtr makenode(double x, double y, double z){
    NodePtr newnode = (NodePtr)malloc(sizeof(Node));
    if(!newnode){fprintf(stderr, "errore\n"); exit(1);}
    newnode->x = x;
    newnode->y = y;
    newnode->z = z;
    newnode->next = NULL;
    return newnode;
}

List insert(List L, NodePtr node){
        node->next = L;
    return node;
}

void print(const List L){
        if(!L) return;
    printf("coefficiente x:%lf\ncoefficiente x:%lf\ncoefficiente x:%lf\n\n", L->x, L->y, L->z);
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
void calcola_espressione(const List L){
    NodePtr res = makenode(0.0, 0.0, 0.0);
    calcola_espressione_rec(L, res);
    printf("%lfx + %lfy + %lfz\n", res->x, res->y, res->z);
    free(res);
    return;
}

void calcola_espressione_rec(const List L, NodePtr res){
    if(!L) return;
    res->x += L->x;
    res->y += L->y;
    res->z += L->z;
    calcola_espressione_rec(L->next, res);
    return;
}