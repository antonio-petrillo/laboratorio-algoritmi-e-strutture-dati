#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"
#include "sl_list.h"

SL_List function(Btree tree);
void function_helper(Btree tree, SL_List* list, unsigned int level);

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  Btree tree = makeBtree();
  srand(time(NULL));
  for(int i=0; i<atoi(argv[1]); i++)tree = insertBtree(tree, rand()%100 + 1);
  inOrderBtree(tree);
  printf("\nesecuzione esercizio\n");
  SL_List list = function(tree);
  printf("nodi che si trovano ad un livello pari\n");
  print_sl(list);
  tree = dropBtree(tree);
  list = drop_sl(list);
  return 0;
}

SL_List function(Btree tree){
  SL_List list = makelist_sl();
  function_helper(tree, &list, 0);
  return list;
}

void function_helper(Btree tree, SL_List* list, unsigned int level){
  if(tree){
    if(level%2 == 0) *list = insert_in_head_sl(*list, tree->value);
    function_helper(tree->left, list, level+1);
    function_helper(tree->right, list, level+1);
  }
  return;
}
