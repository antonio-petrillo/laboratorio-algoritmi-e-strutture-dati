#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree.h"

Btree function(Btree tree, int key);

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  Btree tree = makeBtree();
  srand(time(NULL));
  for(int i=0; i<atoi(argv[1]); i++)tree = insertBtree(tree, rand()%100 + 1);
  inOrderBtree(tree);
  printf("\nesecuzione esercizio\n");
  BnodePtr minSubTree = function(tree, 42);
  if(minSubTree){
    printf("%s%d\n", "valore minimo del sottoalbero radiato in 42 : ", minSubTree->value);
  }else printf("%s\n", "valore non presente nell'albero");
  tree = dropBtree(tree);
  return 0;
}

Btree function(Btree tree, int key){
  BnodePtr found = searchBtree(tree, key);
  return (found) ? minBtree(found) : NULL;
}
