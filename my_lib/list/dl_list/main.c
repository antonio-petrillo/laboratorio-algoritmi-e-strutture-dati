#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dl_list.h"

int main(int argc, char** argv){
	srand(time(NULL));
	DL_NodePtr LH = makelist_dl();
	for(int i=0; i<10; i++) LH = insert_in_head_dl(LH, i);
	printf("stampa della lista con inserimento in testa\n");
	print_dl(LH);
	printf("prova funzione search\n");
	DL_NodePtr res = search_dl(LH, 4);
	printf("valore estratto(-1 non presente per semplicita'): %d\n", (res) ? res->value : -1);
	LH = drop_dl(LH);
	return 0;
}
