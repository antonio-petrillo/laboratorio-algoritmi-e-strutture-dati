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
SL_NodePtr makenode_sl(int value);
SL_List insert_in_head_sl(SL_List L, int value);
SL_List insert_in_tail_sl(SL_List L, int value);
SL_List insert_in_order_sl(SL_List L, int value);
SL_List insert_node_in_head_sl(SL_List L, SL_NodePtr node);
SL_List insert_node_in_tail_sl(SL_List L, SL_NodePtr node);
SL_List insert_node_in_order_sl(SL_List L, SL_NodePtr node);
SL_List copy_sl(SL_List L);
SL_List order_sl(SL_List L);
SL_List remove_duplicates_sl(SL_List L);
void remove_with_key_sl(SL_List* L, int key);
const SL_NodePtr min_sl(const SL_List L);
const SL_NodePtr max_sl(const SL_List L);
unsigned int sl_len(const SL_List L);
int is_empty_sl(const SL_List L);
const SL_NodePtr search_sl(const SL_List L, int value);
void print_sl(const SL_List L);
SL_List drop_sl(SL_List L);

SL_NodePtr sl_union(const SL_NodePtr L1, const SL_NodePtr L2);
void sl_union_rec(const SL_NodePtr L1, const SL_NodePtr L2, SL_NodePtr* L3);
SL_NodePtr sl_intersect(const SL_NodePtr L1, const SL_NodePtr L2);
void sl_intersect_rec(const SL_NodePtr L1, const SL_NodePtr L2, SL_NodePtr* L3);
SL_NodePtr sl_difference(const SL_NodePtr L1, const SL_NodePtr L2);
void sl_difference_rec(const SL_NodePtr L1, const SL_NodePtr L2, SL_NodePtr* L3);

#endif
