#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "library_manager.h"

#define CREATE_BACKUP 1
//if undef CREATE_BACKUP the program doesn't create automatically a backup of library file

int main(int argc, char** argv){
    if(argc < 2){
        printf("this program need a filename (with extension) as first input of the program\n");
        return -1;
    }
    
    printf("\n########### START PROGRAM ############\n");
    library_manager_t library_manager = make_library_manager(argv[1]);
    printf("\n########### LIBRARY LOADED ############\n");

    #ifdef CREATE_BACKUP
        printf("\n########### CREATE LIBRARY BACKUP ############\n");
        create_backup(library_manager);
    #endif

    printf("\n########### START HANDLING REQUEST ############\n\n\n");
    handle_library_request(library_manager);

    printf("\n\n########### STORE PROGESS ############\n");
    store_loan_list(library_manager);
    store_request(library_manager);
    store_library(library_manager);

    delete_library(library_manager);


    printf("\n\n########### END PROGRAM ############\n");

    return 0;
}