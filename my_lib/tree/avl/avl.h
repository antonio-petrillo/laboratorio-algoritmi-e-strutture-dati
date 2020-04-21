#ifndef AVL_H
#define AVL_H 1

typedef struct avl_node{
	struct avl_node* left;
	struct avl_node* right;
	int value;
	unsigned int height;
}avlNode;

typedef avlNode* avlNodePtr;
typedef avlNodePtr avlTree;


void avlError(char* message);
avlTree makeAvlTree();
avlNodePtr makeAvlNode(int value);

//insert
avlTree insertAvl(avlTree tree, int value);
int isSl(avlNodePtr node);
int isSr(avlNodePtr node);
unsigned int maxHeight(avlNodePtr node1, avlNodePtr node2);
avlNodePtr leftBalance(avlNodePtr node);
avlNodePtr rightBalance(avlNodePtr node);
avlNodePtr leftRotate(avlNodePtr node);
avlNodePtr rightRotate(avlNodePtr node);
avlNodePtr doubleLeftRotate(avlNodePtr node);
avlNodePtr doubleRightRotate(avlNodePtr node);

//delete tree
avlTree dropAvl(avlTree tree);

//delete node
avlTree deleteAvlNode(avlTree tree, int value);
//support function for deleteAvlNode
avlNodePtr minAvlDeconnection(avlNodePtr child, avlNodePtr parent);
avlNodePtr deletAvlRoot(avlNodePtr root);


int countAvlTree(avlTree root);
avlNodePtr maxAvlTree(avlTree root);
avlNodePtr minAvlTree(avlTree root);
int isEmptyAvlTree(avlTree root);
avlNodePtr searchAvlTree(avlTree root, int value);
void inOrderAvlTree(avlTree root);
void preOrderAvlTree(avlTree root);
void postOrderAvlTree(avlTree root);
avlTree unionAvlTree(avlTree tree1, avlTree tree2);
avlTree intersectAvlTree(avlTree tree1, avlTree tree2);
avlTree differenceAvlTree(avlTree tree1, avlTree tree2);
void unionAvlTree_rc(avlTree tree1, avlTree tree2, avlTree* tree3);
void intersectAvlTree_rc(avlTree tree1, avlTree tree2, avlTree* tree3);
void differenceAvlTree_rc(avlTree tree2, avlTree* tree3);
avlTree copyAvlTree(avlTree tree);
void copyAvlTree_rec(avlTree tree, avlTree* copy);
void removeDuplicatesAvlTree(avlTree* tree);
avlNodePtr successorAvlTree(avlTree tree, int value);
void successorAvlTree_rec(avlTree root, int value, avlNodePtr* candidate);
avlNodePtr predeccessorAvlTree(avlTree tree, int value);
void predecessorAvlTree_rec(avlTree root, int value, avlNodePtr* candidate);

#endif
