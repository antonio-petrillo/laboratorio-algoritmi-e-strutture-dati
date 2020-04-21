#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void avlError(char* message){
	fprintf(stderr, "%s\n", message);
	exit(1);
}

avlTree makeAvlTree(){
	return NULL;
}

avlNodePtr makeAvlNode(int value){
	avlNodePtr newnode = (avlNodePtr)malloc(sizeof(avlNode));
	if(!newnode) avlError("no memory available");
	newnode->right = newnode->left = NULL;
	newnode->height = 0;
	newnode->value = value;
	return newnode;
}

avlTree insertAvl(avlTree tree, int value){
	if(!tree) tree = makeAvlNode(value);
	else if(tree->value > value){
		tree->left = insertAvl(tree->left, value);
		tree = leftBalance(tree);
	}else{
		tree->right = insertAvl(tree->right, value);
		tree = rightBalance(tree);
	}
	return tree;
}

int isSl(avlNodePtr node){
	return (node->left->height > node->right->height) ? 1 : 0;
}

int isSr(avlNodePtr node){
	return (node->right->height > node->left->height) ? 1 : 0;
}

unsigned int maxHeight(avlNodePtr node1, avlNodePtr node2){
	unsigned int max = -1;
	if(node1 && node2) max = (node1->height > node2->height) ?  node1->height : node2->height;
	else if(!node1 && node2) max = node2->height;
	else if(node1 && !node2) max = node1->height;
	return max;
}

avlNodePtr leftBalance(avlNodePtr node){
	if(node){
		if(node->left && node->right){
			if(node->left->height - node->right->height == 2){
				if(isSl(node)) node = leftRotate(node);
				else node =doubleLeftRotate(node);
			}else node->height = 1 + maxHeight(node->left, node->right);
		}
	}
	return node;
}

avlNodePtr rightBalance(avlNodePtr node){
	if(node){
		if(node->left && node->right){
			if(node->right->height - node->left->height == 2){
				if(isSr(node)) node = rightRotate(node);
				else node = doubleRightRotate(node);
			}else node->height = 1 + maxHeight(node->left, node->right);
		}
	}
	return node;
}

avlNodePtr leftRotate(avlNodePtr node){
	avlNodePtr newroot = node;
	if(node->left){
		newroot = node->left;
		node->left = newroot->right;
		newroot->right = node;
		node->height = 1 + maxHeight(node->left, node->right);
		newroot->height = 1 + maxHeight(newroot->left, newroot->right);
	}
	return newroot;
}

avlNodePtr rightRotate(avlNodePtr node){
	avlNodePtr newroot = node;
	if(node->left){
		newroot = node->right;
		node->right = newroot->left;
		newroot->left = node;
		node->height = 1 + maxHeight(node->left, node->right);
		newroot->height = 1 + maxHeight(newroot->left, newroot->right);
	}
	return newroot;
}

avlNodePtr doubleLeftRotate(avlNodePtr node){
	node->left = rightRotate(node->left);
	return leftBalance(node);
}

avlNodePtr doubleRightRotate(avlNodePtr node){
	node->right = leftRotate(node->right);
	return rightBalance(node->left);
}


avlTree deleteAvlNode(avlTree tree, int value){
	if(tree){
		if(tree->value > value){
			tree->left = deleteAvlNode(tree->left, value);
			tree = rightBalance(tree);
		}else if(tree->value < value){
			tree->right = deleteAvlNode(tree->right, value);
			tree = leftBalance(tree);
		}else{
			if(!(tree->left && tree->right)) tree = deletAvlRoot(tree);
			else{
				avlNodePtr min = minAvlDeconnection(tree->right, tree);
				tree->value = min->value;
				free(min);
			}
		}
	}
	return tree;
}

avlNodePtr minAvlDeconnection(avlNodePtr child, avlNodePtr parent){
	if(child->left) return minAvlDeconnection(child, child->left);
  else {
    if(child == parent->right) parent->right = child->right;
    else parent->left = child->right;
    return child;
  }
}

avlNodePtr deletAvlRoot(avlNodePtr root){
	avlNodePtr tmp = NULL;
	if(root->left) tmp = root->left;
	else tmp = root->right;
	free(root);
	return tmp;
}

avlTree dropAvl(avlTree tree){
	if(tree){
		tree->left = dropAvl(tree->left);
		tree->right = dropAvl(tree->right);
		free(tree);
	}
	return NULL;
}

int countAvlTree(avlTree root){
    if(root) return countAvlTree(root->left) + countAvlTree(root->right) + 1;
    return 0;
}

avlNodePtr minAvlTree(avlTree root){
    if(!root) return NULL;
    return (root->left) ? minAvlTree(root->left) : root;
}

avlNodePtr maxAvlTree(avlTree root){
  if(!root) return NULL;
  return (root->right) ? maxAvlTree(root->right) : root;
}

int isEmptyAvlTree(avlTree root){
  return root == NULL;
}

avlNodePtr searchAvlTree(avlTree root, int value){
    if(!root) return NULL;
    else{
      if(root->value > value) return searchAvlTree(root->left, value);
      else if(root->value < value) return searchAvlTree(root->right, value);
      else return root;
    }
}

void inOrderAvlTree(avlTree root){
    if(!root) return;
    inOrderAvlTree(root->left);
    printf("valore del nodo: %d\n", root->value);
    inOrderAvlTree(root->right);
    return;
}

void preOrderAvlTree(avlTree root){
  if(!root) return;
  printf("valore del nodo: %d\n", root->value);
  preOrderAvlTree(root->left);
  preOrderAvlTree(root->right);
  return;
}

void postOrderAvlTree(avlTree root){
  if(!root) return;
  postOrderAvlTree(root->left);
  postOrderAvlTree(root->right);
  printf("valore del nodo: %d\n", root->value);
  return;
}

avlTree unionAvlTree(avlTree tree1, avlTree tree2){
  avlTree ret = makeAvlTree();
  unionAvlTree_rc(tree1, tree2, &ret);
  return ret;
}

avlTree intersectAvlTree(avlTree tree1, avlTree tree2){
  avlTree ret = makeAvlTree();
  if(tree1) intersectAvlTree_rc(tree1, tree2, &ret);
  return ret;
}

avlTree differenceAvlTree(avlTree tree1, avlTree tree2){
  avlTree ret = makeAvlTree();
  if(tree1) {
	ret = copyAvlTree(tree1);
	removeDuplicatesAvlTree(&ret);
	differenceAvlTree_rc(tree2, &ret);
  }
  return ret;
}

void unionAvlTree_rc(avlTree tree1, avlTree tree2, avlTree* tree3){
    if(!tree1 && !tree2){
      //do nothing
    }else if(tree1 && !tree2){
      if(!searchAvlTree(*tree3, tree1->value)) *tree3 = insertAvl(*tree3, tree1->value);
      unionAvlTree_rc(tree1->left, tree2, tree3);
      unionAvlTree_rc(tree1->right, tree2, tree3);
    }else if(!tree1 && tree2){
      if(!searchAvlTree(*tree3, tree2->value)) *tree3 = insertAvl(*tree3, tree2->value);
      unionAvlTree_rc(tree1, tree2->left, tree3);
      unionAvlTree_rc(tree1, tree2->right, tree3);
    }else{
      if(!searchAvlTree(*tree3, tree1->value)) *tree3 = insertAvl(*tree3, tree1->value);
      if(!searchAvlTree(*tree3, tree2->value)) *tree3 = insertAvl(*tree3, tree2->value);
      unionAvlTree_rc(tree1->left, tree2, tree3);
      unionAvlTree_rc(tree1->right, tree2, tree3);
      unionAvlTree_rc(tree1, tree2->left, tree3);
      unionAvlTree_rc(tree1, tree2->right, tree3);
    }
    return;
}

void intersectAvlTree_rc(avlTree tree1, avlTree tree2, avlTree* tree3){
    if(tree2){
      if(searchAvlTree(tree1, tree2->value))
        if(!searchAvlTree(*tree3, tree2->value))
          *tree3 = insertAvl(*tree3, tree2->value);
      intersectAvlTree_rc(tree1, tree2->left, tree3);
      intersectAvlTree_rc(tree1, tree2->right, tree3);
    }
    return;
}

void differenceAvlTree_rc(avlTree tree2, avlTree* tree3){
  if(tree2){
    if(searchAvlTree(*tree3, tree2->value))
      *tree3 = deleteAvlNode(*tree3, tree2->value);
    differenceAvlTree_rc(tree2->left, tree3);
    differenceAvlTree_rc(tree2->right, tree3);
  }
  return;
}

avlTree copyAvlTree(avlTree tree){
  avlTree copy = makeAvlTree();
  copyAvlTree_rec(tree, &copy);
  return copy;
}

void copyAvlTree_rec(avlTree tree, avlTree* copy){
  if(!tree) return;
  *copy = insertAvl(*copy, tree->value);
  copyAvlTree_rec(tree->left, copy);
  copyAvlTree_rec(tree->right, copy);
  return;
}

void removeDuplicatesAvlTree(avlTree* tree){
  if(!(*tree)) return;
  if(searchAvlTree((*tree)->left, (*tree)->value)){
    (*tree)->left = deleteAvlNode((*tree)->left, (*tree)->value);
  }if(searchAvlTree((*tree)->right, (*tree)->value)){
    (*tree)->right = deleteAvlNode((*tree)->right, (*tree)->value);
  }
  removeDuplicatesAvlTree(&(*tree)->left);
  removeDuplicatesAvlTree(&(*tree)->right);
  return;
}

avlNodePtr successorAvlTree(avlTree tree, int value){
    avlNodePtr ret = NULL;
    successorAvlTree_rec(tree, value, &ret);
    return ret;
}

// ogni volta che scendo a sinistra devo salvare il nodo
void successorAvlTree_rec(avlTree root, int value, avlNodePtr* candidate){
  if(root){
    if(root->value > value){
      *candidate = root;
      successorAvlTree_rec(root->left, value, candidate);
    }else if(root->value < value){
      successorAvlTree_rec(root->right, value, candidate);
    }else{
      avlNodePtr tmp = minAvlTree(root->right);
      *candidate = (tmp) ? tmp : (*candidate);
    }
  }
  return;
}

avlNodePtr predeccessorAvlTree(avlTree tree, int value){
  avlNodePtr ret = NULL;
  predecessorAvlTree_rec(tree, value, &ret);
  return ret;
}

void predecessorAvlTree_rec(avlTree root, int value, avlNodePtr* candidate){
  if(root){
    if(root->value > value){
      predecessorAvlTree_rec(root->left, value, candidate);
    }else if(root->value < value){
      *candidate = root;
      predecessorAvlTree_rec(root->right, value, candidate);
    }else{
      avlNodePtr tmp = maxAvlTree(root->left);
      *candidate = (tmp) ? tmp : (*candidate);
    }
  }
  return;
}