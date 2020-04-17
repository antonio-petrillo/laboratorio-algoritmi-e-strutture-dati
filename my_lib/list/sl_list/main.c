#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sl_list.h"

int main(int argc, char** argv){
	srand(time(NULL));
	SL_NodePtr LH = makelist_sl();
	SL_NodePtr LT = makelist_sl();
	SL_NodePtr LO = makelist_sl();
	for(int i=0; i<10; i++) LH = insert_in_head(LH, i);
	for(int i=0; i<10; i++) LT = insert_in_tail(LT, i);
	for(int i=0; i<10; i++) LO = insert_in_order(LO, rand()%10);
	printf("stampa della lista con inserimento in testa\n");
	print_sl(LH);
	printf("stampa della lista con inserimento in coda\n");
	print_sl(LT);
	printf("stampa della lista con inserimento ordinato\n");
	print_sl(LO);
	printf("prova funzione search\n");
	SL_NodePtr res = search(LH, 4);
	printf("valore estratto(-1 non presente per semplicita'): %d\n", (res) ? res->value : -1);
	LH = drop_sl(LH);
	LT = drop_sl(LT);
	LO = drop_sl(LO);
	return 0;
}
