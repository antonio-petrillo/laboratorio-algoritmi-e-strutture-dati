#ifndef RBTREE_H
#define RBTREE_H

typedef enum{RED, BLACK, DOUBLE_BLACK, WHITE} Color;

typedef struct rb_node{
  struct rb_node* left;
  struct rb_node* right;
  int value;
  Color color;
}rbNode;

typedef rbNode* rbNodePtr;
typedef rbNodePtr rbTree;


void rbError(char* message);
rbTree makeRbTree();
rbNodePtr makeRbNode(int value);
rbTree insertRb(rbTree tree, int value);
rbTree insertRb_rec(rbTree tree, int value);
rbTree deleteRbNode(rbTree tree, int value);
rbTree deleteRbNode_rec(rbTree tree, int value);
rbNodePtr minDeconnectionRb(rbNodePtr child, rbNodePtr parent);
rbNodePtr propagateBlack(rbNodePtr root);
rbTree dropRb(rbTree tree);

//left
rbNodePtr leftRotate(rbNodePtr root);
//left insert
rbNodePtr leftInsertBalance(rbNodePtr root);
int typeInsertViolationLeft(rbNodePtr root);
rbNodePtr insertBalanceLeft_1(rbNodePtr root);
rbNodePtr insertBalanceLeft_2(rbNodePtr root);
rbNodePtr insertBalanceLeft_3(rbNodePtr root);
//left delete
rbNodePtr leftDeleteBalance(rbNodePtr root);
int typeDeleteViolationLeft(rbNodePtr root);
rbNodePtr deleteBalanceLeft_1(rbNodePtr root);
rbNodePtr deleteBalanceLeft_2(rbNodePtr root);
rbNodePtr deleteBalanceLeft_3(rbNodePtr root);
rbNodePtr deleteBalanceLeft_4(rbNodePtr root);

//right
rbNodePtr rightRotate(rbNodePtr root);
//right insert
rbNodePtr rightInsertBalance(rbNodePtr root);
int typeInsertViolationRight(rbNodePtr root);
rbNodePtr insertBalanceRight_1(rbNodePtr root);
rbNodePtr insertBalanceRight_2(rbNodePtr root);
rbNodePtr insertBalanceRight_3(rbNodePtr root);
//right delete
rbNodePtr rightDeleteBalance(rbNodePtr root);
int typeDeleteViolationRight(rbNodePtr root);
rbNodePtr deleteBalanceRight_1(rbNodePtr root);
rbNodePtr deleteBalanceRight_2(rbNodePtr root);
rbNodePtr deleteBalanceRight_3(rbNodePtr root);
rbNodePtr deleteBalanceRight_4(rbNodePtr root);

//just for test it's a normal in order visit
void print(rbTree tree);

#endif
