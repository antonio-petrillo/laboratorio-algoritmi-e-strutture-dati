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
avlTree dropAvl(avlTree tree);

avlTree deleteAvlNode(avlTree tree, int value);
//support function for deleteAvlNode
avlNodePtr minAvlDeconnection(avlNodePtr child, avlNodePtr parent);
avlNodePtr deletAvlRoot(avlNodePtr root);



//just for test it's a normal in order visit on a bst
void print(avlTree tree);

#endif
