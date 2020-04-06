#ifndef SL_LIST_H
#define SL_LIST_H 1

typedef struct sl_node{
	int value;
	struct sl_node* next;
}SL_Node;

typedef SL_Node* SL_NodePtr;

SL_NodePtr makelist_sl();
void sl_error(char* message);
SL_NodePtr makenode(int value);
SL_NodePtr insert_in_head(SL_NodePtr L, int value);
SL_NodePtr insert_in_tail(SL_NodePtr L, int value);
SL_NodePtr insert_in_order(SL_NodePtr L, int value);
SL_NodePtr insert_node_in_head(SL_NodePtr L, SL_NodePtr node);
SL_NodePtr insert_node_in_tail(SL_NodePtr L, SL_NodePtr node);
SL_NodePtr insert_node_in_order(SL_NodePtr L, SL_NodePtr node);
SL_NodePtr order(SL_NodePtr L);
SL_NodePtr remove_with_key(SL_NodePtr L, int key);
const SL_NodePtr min(const SL_NodePtr L);
const SL_NodePtr max(const SL_NodePtr L);
unsigned int sl_len(const SL_NodePtr L);
int is_empty(const SL_NodePtr L);
const SL_NodePtr search(const SL_NodePtr L, int value);
void print_sl(const SL_NodePtr L);
SL_NodePtr drop_sl(SL_NodePtr L);

#endif
