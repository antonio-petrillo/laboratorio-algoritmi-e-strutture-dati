#include <stdio.h>
#include <stdlib.h>

typedef struct piatto{
    struct piatto* next;
}Piatto;

typedef struct{
    Piatto* primo_piatto;
}Pila_piatti_da_lavare;

void crea_pila(Pila_piatti_da_lavare* p);
void aggiungi_piatto_alla_pila(Pila_piatti_da_lavare* p);
void lavoro_part_time_a_Londra_prima_della_Brexit(Pila_piatti_da_lavare* p);

int main(int argc, char** argv){
    Pila_piatti_da_lavare p;
    crea_pila(&p);
    for(int i=0; i<atoi(argv[1]); i++) aggiungi_piatto_alla_pila(&p);
    lavoro_part_time_a_Londra_prima_della_Brexit(&p);
    return 0;
}

void crea_pila(Pila_piatti_da_lavare* p){
    p->primo_piatto = NULL;
    return;
}

void aggiungi_piatto_alla_pila(Pila_piatti_da_lavare* p){
    Piatto* nuovo_piatto = (Piatto*) malloc(sizeof(Piatto));
    if(!nuovo_piatto){printf("impossibile allocare lo spazio per il piatto!\n"); exit(1);}
    nuovo_piatto->next = p->primo_piatto;
    p->primo_piatto = nuovo_piatto;
    return;
}

void lavoro_part_time_a_Londra_prima_della_Brexit(Pila_piatti_da_lavare* p){
    if(p->primo_piatto){
        Piatto* tmp = p->primo_piatto;
        p->primo_piatto = tmp->next;
        free(tmp);
        printf("piatto lavato\n");
        lavoro_part_time_a_Londra_prima_della_Brexit(p);
    }else{ printf("pila vuota, tutti ia piatti sono stati lavati\n"); exit(1);}
}