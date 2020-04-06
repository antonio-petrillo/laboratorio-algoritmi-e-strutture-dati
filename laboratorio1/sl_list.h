#ifndef SL_LIST_H
#define SL_LIST_H 1

typedef struct sl_node{
	int value;
	struct sl_node* next;
}SL_Node;

typedef SL_Node* SL_NodePtr;
typedef SL_NodePtr SL_List;

SL_List makelist_sl();
void sl_error(char* message);
SL_NodePtr makenode(int value);
SL_List insert_in_head(SL_List L, int value);
SL_List insert_in_tail(SL_List L, int value);
SL_List insert_in_order(SL_List L, int value);
SL_List insert_node_in_head(SL_List L, SL_NodePtr node);
SL_List insert_node_in_tail(SL_List L, SL_NodePtr node);
SL_List insert_node_in_order(SL_List L, SL_NodePtr node);
SL_List copy(SL_List L);
SL_List order(SL_List L);
SL_List remove_duplicates(SL_List L);
SL_NodePtr remove_with_key(SL_List L, int key);
const SL_NodePtr min(const SL_List L);
const SL_NodePtr max(const SL_List L);
unsigned int sl_len(const SL_List L);
int is_empty(const SL_List L);
const SL_NodePtr search(const SL_List L, int value);
void print_sl(const SL_List L);
SL_List drop_sl(SL_List L);

#endif
