#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

void rbError(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

rbTree makeRbTree(){
    return NULL;
}

rbNodePtr makeRbNode(int value){
    rbNodePtr newnode = (rbNodePtr)malloc(sizeof(rbNode));
    if(!newnode)rbError("no memory available");
    newnode->left = newnode->right = NULL;
    newnode->color = RED;
    newnode->value = value;
    return newnode;
}

rbTree insertRb(rbTree tree, int value){
  tree = insertRb_rec(tree, value);
  tree->color = BLACK;
  return tree;
}

rbTree insertRb_rec(rbTree tree, int value){
  if(!tree) tree = makeRbNode(value);
  else if(tree->value > value){
    tree->left = insertRb_rec(tree->left, value);
    tree = leftInsertBalance(tree);
  }else{
    tree->right = insertRb_rec(tree->right, value);
    tree = rightInsertBalance(tree);
  }
  return tree;
}

rbTree dropRb(rbTree tree){
  if(tree){
    tree->left = dropRb(tree->left);
    tree->right = dropRb(tree->right);
    free(tree);
  }
  return NULL;
}

void print(rbTree tree){
    if(tree){
      print(tree->left);
      printf("valore del nodo: %d\n", tree->value);
      print(tree->right);
    }
    return;
}
//left
rbNodePtr leftRotate(rbNodePtr root){
    rbNodePtr newroot = root;
    if(root){
      if(root->left){
        newroot = root->left;
        root->left = newroot->right;
        newroot->right = root;
      }
    }
    return newroot;
}

rbNodePtr leftInsertBalance(rbNodePtr root){
  switch (typeInsertViolationLeft(root)) {
    case 1:
      root = insertBalanceLeft_1(root);
      break;
    case 2:
      root = insertBalanceLeft_2(root);
      break;
    case 3:
      root = insertBalanceLeft_3(root);
      break;
    default:
      //do nothing
      break;
  }
  return root;
}

int typeInsertViolationLeft(rbNodePtr root){
  int violation = 0;
  if(root->right && root->right->color == RED){
    if(root->left && root->left->color == RED){
      if(root->left->left && root->left->left->color == RED)
        violation = 1;
      else if(root->left->right && root->left->right->color == RED)
        violation = 1;
    }
  }else {
    if(root->left->left && root->left->left->color == RED)
      violation = 2;
    else if(root->left->right && root->left->right->color == RED)
      violation = 3;
  }
  return violation;
}

rbNodePtr insertBalanceLeft_1(rbNodePtr root){
    root->left->color = root->right->color = BLACK;
    root->color = RED;
    return root;
}

rbNodePtr insertBalanceLeft_2(rbNodePtr root){
  root = leftRotate(root);
  root->left->color = RED;
  root->color = BLACK;
  return root;
}

rbNodePtr insertBalanceLeft_3(rbNodePtr root){
  root->left = rightRotate(root->left);
  root = insertBalanceLeft_2(root);
  return root;
}

//right
rbNodePtr rightRotate(rbNodePtr root){
  rbNodePtr newroot = root;
  if(root){
    if(root->right){
      newroot = root->right;
      root->right = newroot->left;
      newroot->left = root;
    }
  }
  return newroot;
}

rbNodePtr rightInsertBalance(rbNodePtr root){
  switch (typeInsertViolationRight(root)) {
    case 1:
      root = insertBalanceRight_1(root);
      break;
    case 2:
      root = insertBalanceRight_2(root);
      break;
    case 3:
      root = insertBalanceRight_3(root);
      break;
    default:
      //do nothing
      break;
  }
  return root;
}

int typeInsertViolationRight(rbNodePtr root){
  int violation = 0;
  if(root->left && root->left->color == RED){
    if(root->right && root->right->color == RED){
      if(root->right->left && root->right->left->color == RED)
        violation = 1;
      else if(root->right->right && root->right->right->color == RED)
        violation = 1;
    }
  }else {
    if(root->right->right && root->right->right->color == RED)
      violation = 2;
    else if(root->right->left && root->right->left->color == RED)
      violation = 3;
  }
  return violation;
}

rbNodePtr insertBalanceRight_1(rbNodePtr root){
  root->left->color = root->right->color = BLACK;
  root->color = RED;
  return root;
}

rbNodePtr insertBalanceRight_2(rbNodePtr root){
  root = rightRotate(root);
  root->right->color = RED;
  root->color = BLACK;
  return root;
}
rbNodePtr insertBalanceRight_3(rbNodePtr root){
  root->left = leftRotate(root->left);
  root = insertBalanceRight_2(root);
  return root;
}

rbTree deleteRbNode(rbTree tree, int value){
    tree = deleteRbNode_rec(tree, value);
    tree->color = BLACK;
    return tree;
}

rbTree deleteRbNode_rec(rbTree tree, int value){
  if(tree){
    if(tree->value > value){
      tree->left = deleteRbNode_rec(tree->left, value);
      tree = leftDeleteBalance(tree);
    }else if(tree->value < value){
      tree->right = deleteRbNode_rec(tree->right, value);
      tree = rightDeleteBalance(tree);
    }else{
      if(!(tree->left && tree->right)){
        rbNodePtr tmp = tree;
        if(tree->left) tree = tree->left;
        else tree = tree->right;
        free(tmp);
        tree = propagateBlack(tree);
      }else{
        rbNodePtr min = minDeconnectionRb(tree->right, tree);
        tree->value = min->value;
        free(min);
        tree = rightDeleteBalance(tree);
      }
    }
  }
  return tree;
}

rbNodePtr minDeconnectionRb(rbNodePtr child, rbNodePtr parent){
  rbNodePtr retNode = NULL;
  if(child->left){
    retNode = minDeconnectionRb(child->left, child);
    if(child == parent->left) parent->left = leftDeleteBalance(parent);
    else parent->right = rightDeleteBalance(parent);
  }else{
    retNode = child;
    if(child == parent->right) parent->right = child->right;
    else parent->left = child->right;
  }
  return retNode;
}

rbNodePtr propagateBlack(rbNodePtr root){
  if(root->color) root->color = DOUBLE_BLACK;
  else root->color = BLACK;
  return root;
}

rbNodePtr leftDeleteBalance(rbNodePtr root){
  if(root->left || root->right){
    switch (typeDeleteViolationLeft(root)) {
      case 1:
        root = deleteBalanceLeft_1(root);
        root->left = leftDeleteBalance(root->left);
        break;
      case 2:
        root = deleteBalanceLeft_2(root);
        break;
      case 3:
        root = deleteBalanceLeft_3(root);
        root = deleteBalanceLeft_4(root);
        break;
      case 4:
        root = deleteBalanceLeft_4(root);
        break;
      default:
        //do nothing
        break;
    }
  }
  return root;
}

int typeDeleteViolationLeft(rbNodePtr root){
    int violation = 0;
    if(root->left && root->right){
        if(root->left->color == DOUBLE_BLACK && root->right->color == RED) violation = 1;
        else if(root->left->color == DOUBLE_BLACK){
            violation = 2;
            if(root->right->right && root->right->right->color == RED) violation = 4;
            else if(root->right->left && root->right->left->color == RED) violation = 3;
        }
    }
    return violation;
}

rbNodePtr deleteBalanceLeft_1(rbNodePtr root){
  root = rightRotate(root);
  root->left->color = RED;
  root->color = BLACK;
  return root;
}

rbNodePtr deleteBalanceLeft_2(rbNodePtr root){
  root->right->color = RED;
  root->left->color = BLACK;
  root = propagateBlack(root);
  return root;
}

rbNodePtr deleteBalanceLeft_3(rbNodePtr root){
  root->right = leftRotate(root->right);
  root->right->color = BLACK;
  root->right->right->color = RED;
  return root;
}

rbNodePtr deleteBalanceLeft_4(rbNodePtr root){
  root = rightRotate(root);
  root->right->color = BLACK;
  root->color = root->left->color;
  root->left->color = BLACK;
  root->left->left->color = BLACK;
  return root;
}

rbNodePtr rightDeleteBalance(rbNodePtr root){
  if(root->right || root->left){
    switch (typeDeleteViolationRight(root)) {
      case 1:
        root = deleteBalanceRight_1(root);
        root->right = rightDeleteBalance(root->right);
        break;
      case 2:
        root = deleteBalanceRight_2(root);
        break;
      case 3:
        root = deleteBalanceRight_3(root);
        root = deleteBalanceRight_4(root);
        break;
      case 4:
        root = deleteBalanceRight_4(root);
        break;
      default:
        //do nothing
        break;
    }
  }
  return root;
}

int typeDeleteViolationRight(rbNodePtr root){
  int violation = 0;
  if(root->right && root->right->color == DOUBLE_BLACK){
    violation = 2;
    if(root->left){
      if(root->left->color = RED) violation = 1;
      else if(root->left->right && root->left->right->color == RED) violation = 3;
      else if(root->left->left && root->left->left->color == RED) violation = 4;
    }
  }
  return violation;
}

rbNodePtr deleteBalanceRight_1(rbNodePtr root){
  root = leftRotate(root);
  root->right->color = RED;
  root->color = BLACK;
  return root;
}

rbNodePtr deleteBalanceRight_2(rbNodePtr root){
  root->right->color = BLACK;
  root->left->color = RED;
  root = propagateBlack(root);
  return root;
}

rbNodePtr deleteBalanceRight_3(rbNodePtr root){
  root->left = rightRotate(root->left);
  root->left->color = BLACK;
  root->left->left->color = RED;
  return root;
}

rbNodePtr deleteBalanceRight_4(rbNodePtr root){
  root = leftRotate(root);
  root->left->color = BLACK;
  root->color = root->right->color;
  root->right->color = BLACK;
  root->right->right->color = BLACK;
  return root;
}
