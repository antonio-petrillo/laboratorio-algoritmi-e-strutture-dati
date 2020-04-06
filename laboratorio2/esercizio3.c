#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char faccia[7];
    char seme[8];
}Carta;

typedef struct giocatore{
    struct giocatore* next;
    struct giocatore* prev;
    Carta carta;
    char* name;
}Giocatore;

typedef Giocatore* GiocatorePtr;
typedef GiocatorePtr lista_giocatori;

lista_giocatori makelist();
GiocatorePtr makenode(Carta c, char* name);
lista_giocatori insert(lista_giocatori list, Carta c, char* name);
lista_giocatori drop(lista_giocatori list);

void print(lista_giocatori l);

lista_giocatori game(lista_giocatori list);

int main(int argc, char** argv){
    FILE* fp = fopen(argv[1], "r");
    if(!fp) exit(1);
    lista_giocatori l = makelist();
    Carta c;
    char buffer[256];
    while(fscanf(fp, "%s%s%s", buffer, c.faccia, c.seme) > 0) l = insert(l, c, buffer);
    printf("stampa della lista\n");
    print(l);
    puts("\n\n");
    l = game(l);
    fclose(fp);
    return 0;
}

lista_giocatori makelist(){
    return NULL;
}

GiocatorePtr makenode(Carta c, char* name){
    GiocatorePtr newnode = (GiocatorePtr)malloc(sizeof(Giocatore));
    newnode->next = newnode->prev = NULL;
    if(!newnode) exit(1);
    newnode->carta = c;
    newnode->name = (char*)calloc(strlen(name)+1, sizeof(char));
    if(!newnode->name) exit(1);
    strcpy(newnode->name, name);
    return newnode;
}

lista_giocatori insert(lista_giocatori list, Carta c, char* name){
    if(!list) return makenode(c, name);
    GiocatorePtr newnode = makenode(c, name);
    newnode->next = list;
    list->prev = newnode;
    return newnode;
}

lista_giocatori drop(lista_giocatori list){
    if(!list)return NULL;
    list->next = drop(list->next);
    free(list);
    return NULL;
}

lista_giocatori game(lista_giocatori list){
    if(!(strcmp(list->carta.seme,"cuori") && strcmp(list->carta.seme,"quadri"))){
        if(list->next){
            printf("il giocatore %s scambia la carta: %s di %s con il giocatore %s in cambio della carta: %s di %s\n\n", list->name, list->carta.faccia, list->carta.seme, list->next->name, list->next->carta.faccia, list->next->carta.seme);
            Carta tmp = list->carta;
            list->carta = list->next->carta;
            list->next->carta = tmp;
            list->next = game(list->next);
            return list;
        }else return list;
    }else{
        if(list->prev){
            printf("il giocatore %s scambia la carta: %s di %s con il giocatore %s in cambio della carta: %s di %s\n\n", list->name, list->carta.faccia, list->carta.seme, list->prev->name, list->prev->carta.faccia, list->prev->carta.seme);
            Carta tmp = list->carta;
            list->carta = list->prev->carta;
            list->prev->carta = tmp;
            list->next = game(list->next);
            return list;
        }else{
            list->next = game(list->next);
            return list;
        }
    }
}

void print(lista_giocatori l){
    if(!l) return;
    printf("giocatore:=%s\t carta:= %s di %s\n", l->name, l->carta.faccia, l->carta.seme);
    print(l->next);
}

