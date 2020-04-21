#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

void BtreeError(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

Btree makeBtree(){
    return NULL;
}

BnodePtr makeBnode(int value){
    BnodePtr newnode = (BnodePtr) malloc(sizeof(Bnode));
    if(!newnode) BtreeError("no available memory");
    newnode->value = value;
    newnode->left = newnode->right = NULL;
    return newnode;
}

Btree insertBtree(Btree root, int value){
  if(root){
      if(root->value > value) root->left = insertBtree(root->left, value);
      else root->right = insertBtree(root->right, value);
      return root;
  }
   return makeBnode(value);
}

Btree removeBnode(Btree root, int value){
  if(root){
    if(root->value > value) root->left = removeBnode(root->left, value);
    else if(root->value < value) root->right = removeBnode(root->right, value);
    else{
      if(!(root->left && root->right)) root = removeBtreeRoot(root);
      else{
        BnodePtr min = minDeconnectionBnode(root, root->right);
        root->value = min->value;
        free(min);
      }
    }
  }
  return root;
}

//support for removeBnode
BnodePtr minDeconnectionBnode(BnodePtr parent, BnodePtr child){
  if(child->left) return minDeconnectionBnode(child, child->left);
  else {
    if(child == parent->right) parent->right = child->right;
    else parent->left = child->right;
    return child;
  }
}

//support for removeBnode
Btree removeBtreeRoot(Btree root){
  BnodePtr tmp = NULL;
  if(root->left) tmp = root->left;
  else tmp = root->right;
  free(root);
  return tmp;
}

Btree dropBtree(Btree root){
  if(!root) return NULL;
  root->left = dropBtree(root->left);
  root->right = dropBtree(root->right);
  free(root);
  return NULL;
}

int countBtree(Btree root){
    if(root) return countBtree(root->left) + countBtree(root->right) + 1;
    return 0;
}

BnodePtr minBtree(Btree root){
    if(!root) return NULL;
    return (root->left) ? minBtree(root->left) : root;
}

BnodePtr maxBtree(Btree root){
  if(!root) return NULL;
  return (root->right) ? maxBtree(root->right) : root;
}

int isEmptyBtree(Btree root){
  return root == NULL;
}

BnodePtr searchBtree(Btree root, int value){
    if(!root) return NULL;
    else{
      if(root->value > value) return searchBtree(root->left, value);
      else if(root->value < value) return searchBtree(root->right, value);
      else return root;
    }
}

void inOrderBtree(Btree root){
    if(!root) return;
    inOrderBtree(root->left);
    printf("valore del nodo: %d\n", root->value);
    inOrderBtree(root->right);
    return;
}

void preOrderBtree(Btree root){
  if(!root) return;
  printf("valore del nodo: %d\n", root->value);
  preOrderBtree(root->left);
  preOrderBtree(root->right);
  return;
}

void postOrderBtree(Btree root){
  if(!root) return;
  postOrderBtree(root->left);
  postOrderBtree(root->right);
  printf("valore del nodo: %d\n", root->value);
  return;
}

Btree unionBtree(Btree tree1, Btree tree2){
  Btree ret = makeBtree();
  unionBtree_rc(tree1, tree2, &ret);
  return ret;
}

Btree intersectBtree(Btree tree1, Btree tree2){
  Btree ret = makeBtree();
  if(tree1) intersectBtree_rc(tree1, tree2, &ret);
  return ret;
}

Btree differenceBtree(Btree tree1, Btree tree2){
  Btree ret = makeBtree();
  if(tree1) {
	  ret = copyBtree(tree1);
	  removeDuplicatesBtree(&ret);
	  differenceBtree_rc(tree1, tree2, &ret);
  }
  return ret;
}

void unionBtree_rc(Btree tree1, Btree tree2, Btree* tree3){
    if(!tree1 && !tree2){
      //do nothing
    }else if(tree1 && !tree2){
      if(!searchBtree(*tree3, tree1->value)) *tree3 = insertBtree(*tree3, tree1->value);
      unionBtree_rc(tree1->left, tree2, tree3);
      unionBtree_rc(tree1->right, tree2, tree3);
    }else if(!tree1 && tree2){
      if(!searchBtree(*tree3, tree2->value)) *tree3 = insertBtree(*tree3, tree2->value);
      unionBtree_rc(tree1, tree2->left, tree3);
      unionBtree_rc(tree1, tree2->right, tree3);
    }else{
      if(!searchBtree(*tree3, tree1->value)) *tree3 = insertBtree(*tree3, tree1->value);
      if(!searchBtree(*tree3, tree2->value)) *tree3 = insertBtree(*tree3, tree2->value);
      unionBtree_rc(tree1->left, tree2, tree3);
      unionBtree_rc(tree1->right, tree2, tree3);
      unionBtree_rc(tree1, tree2->left, tree3);
      unionBtree_rc(tree1, tree2->right, tree3);
    }
    return;
}

void intersectBtree_rc(Btree tree1, Btree tree2, Btree* tree3){
    if(tree2){
      if(searchBtree(tree1, tree2->value))
        if(!searchBtree(*tree3, tree2->value))
          *tree3 = insertBtree(*tree3, tree2->value);
      intersectBtree_rc(tree1, tree2->left, tree3);
      intersectBtree_rc(tree1, tree2->right, tree3);
    }
    return;
}

void differenceBtree_rc(Btree tree1, Btree tree2, Btree* tree3){
  if(tree2){
    if(searchBtree(*tree3, tree2->value))
      *tree3 = removeBnode(*tree3, tree2->value);
    differenceBtree_rc(tree1, tree2->left, tree3);
    differenceBtree_rc(tree1, tree2->right, tree3);
  }
  return;
}

Btree copyBtree(Btree tree){
  Btree copy = makeBtree();
  copyBtree_rec(tree, &copy);
  return copy;
}

void copyBtree_rec(Btree tree, Btree* copy){
  if(!tree) return;
  *copy = insertBtree(*copy, tree->value);
  copyBtree_rec(tree->left, copy);
  copyBtree_rec(tree->right, copy);
  return;
}

void removeDuplicatesBtree(Btree* tree){
  if(!(*tree)) return;
  if(searchBtree((*tree)->left, (*tree)->value)){
    (*tree)->left = removeBnode((*tree)->left, (*tree)->value);
  }if(searchBtree((*tree)->right, (*tree)->value)){
    (*tree)->right = removeBnode((*tree)->right, (*tree)->value);
  }
  removeDuplicatesBtree(&(*tree)->left);
  removeDuplicatesBtree(&(*tree)->right);
  return;
}

BnodePtr successorBtree(Btree tree, int value){
    BnodePtr ret = NULL;
    successorBtree_rec(tree, value, &ret);
    return ret;
}

// ogni volta che scendo a sinistra devo salvare il nodo
void successorBtree_rec(Btree root, int value, BnodePtr* candidate){
  if(root){
    if(root->value > value){
      *candidate = root;
      successorBtree_rec(root->left, value, candidate);
    }else if(root->value < value){
      successorBtree_rec(root->right, value, candidate);
    }else{
      BnodePtr tmp = minBtree(root->right);
      *candidate = (tmp) ? tmp : (*candidate);
    }
  }
  return;
}

BnodePtr predeccessorBtree(Btree tree, int value){
  BnodePtr ret = NULL;
  predecessorBtree_rec(tree, value, &ret);
  return ret;
}

void predecessorBtree_rec(Btree root, int value, BnodePtr* candidate){
  if(root){
    if(root->value > value){
      predecessorBtree_rec(root->left, value, candidate);
    }else if(root->value < value){
      *candidate = root;
      predecessorBtree_rec(root->right, value, candidate);
    }else{
      BnodePtr tmp = maxBtree(root->left);
      *candidate = (tmp) ? tmp : (*candidate);
    }
  }
  return;
}
