#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dl_list.h"


int main(int argc, char** argv){
    srand(time(NULL));
    DL_List list = makelist_dl();
    int range = atoi(argv[2]);
    for(int i=0; i<atoi(argv[1]); i++) list = insert_in_order_dl(list, rand()%range);
    printf("stampa dell alitsa ordinata\n");
    print_dl(list);
    return 0;
}