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

void print(avlTree tree){
	if(tree){
		print(tree->left);
		printf("%s%d\n", "valore del nodo: ", tree->value);
		print(tree->right);
	}
	return ;
}
