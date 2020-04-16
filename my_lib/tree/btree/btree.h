#ifndef BTREE_H
#define	BTREE_H 1

typedef struct btree_node{
  int value;
  struct btree_node* left;
  struct btree_node* right;
}Bnode;

typedef Bnode* BnodePtr;
typedef BnodePtr Btree;

void BtreeError(char* message);
Btree makeBtree();
BnodePtr makeBnode(int value);
Btree insertBtree(Btree root, int value);
Btree removeBnode(Btree root, int value);
BnodePtr minDeconnectionBnode(BnodePtr parent, BnodePtr child);
Btree removeBtreeRoot(Btree root);
Btree dropBtree(Btree root);

int countBtree(Btree root);
BnodePtr maxBtree(Btree root);
BnodePtr minBtree(Btree root);
int isEmptyBtree(Btree root);
BnodePtr searchBtree(Btree root, int value);
void inOrderBtree(Btree root);
void preOrderBtree(Btree root);
void postOrderBtree(Btree root);
Btree unionBtree(Btree tree1, Btree tree2);
Btree intersectBtree(Btree tree1, Btree tree2);
Btree differenceBtree(Btree tree1, Btree tree2);
void unionBtree_rc(Btree tree1, Btree tree2, Btree* tree3);
void intersectBtree_rc(Btree tree1, Btree tree2, Btree* tree3);
void differenceBtree_rc(Btree tree1, Btree tree2, Btree* tree3);
Btree copyBtree(Btree tree);
void copyBtree_rec(Btree tree, Btree* copy);
void removeDuplicatesBtree(Btree* tree);
BnodePtr successorBtree(Btree tree, int value);
void successorBtree_rec(Btree root, int value, BnodePtr* candidate);
BnodePtr predeccessorBtree(Btree tree, int value);
void predecessorBtree_rec(Btree root, int value, BnodePtr* candidate);




#endif
