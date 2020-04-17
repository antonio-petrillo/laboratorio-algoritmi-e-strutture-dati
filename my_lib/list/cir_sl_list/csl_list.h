#ifndef CIR_SL_LIST_H
#define CIR_SL_LIST_H 1

#define HEAD 1
#define NOT_HEAD 0

//CSL :== Circular Single Linked 

typedef struct csl_node{
	int value;
	unsigned int head_of_the_list : 1;
	struct csl_node* next;
}CSL_Node;

typedef CSL_Node* CSL_NodePtr;
typedef CSL_NodePtr CSL_List;

CSL_List makelist_csl();
void csl_error(char* message);
CSL_NodePtr* search_last_sl(CSL_List* L);
CSL_NodePtr makenode_csl(int value);
CSL_List insert_in_head_csl(CSL_List L, int value);
CSL_List insert_in_tail_csl(CSL_List L, int value);
CSL_List insert_in_order_csl(CSL_List L, int value);
CSL_List insert_node_in_head_csl(CSL_List L, CSL_NodePtr node);
CSL_List insert_node_in_tail_csl(CSL_List L, CSL_NodePtr node);
CSL_List insert_node_in_order_csl(CSL_List L, CSL_NodePtr node);
CSL_List copy_csl(const CSL_List L);
CSL_List order_csl(CSL_List L);
CSL_List remove_duplicates_sl(CSL_List L);
void remove_with_key_csl(CSL_List* L, int key);
const CSL_NodePtr min_csl(const CSL_List L);
const CSL_NodePtr max_csl(const CSL_List L);
unsigned int csl_len(const CSL_List L);
int is_empty_csl(const CSL_List L);
const CSL_NodePtr search_csl(const CSL_List L, int value);
void print_csl(const CSL_List L);
CSL_List drop_csl(CSL_List L);

CSL_NodePtr csl_union(const CSL_NodePtr L1, const CSL_NodePtr L2);
void csl_union_rec(const CSL_NodePtr L1, const CSL_NodePtr L2, CSL_NodePtr* L3);
CSL_NodePtr csl_intersect(const CSL_NodePtr L1, const CSL_NodePtr L2);
void csl_intersect_rec(const CSL_NodePtr L1, const CSL_NodePtr L2, CSL_NodePtr* L3);
CSL_NodePtr csl_difference(const CSL_NodePtr L1, const CSL_NodePtr L2);
void csl_difference_rec(const CSL_NodePtr L1, const CSL_NodePtr L2, CSL_NodePtr* L3);

void multi_print_csl(const CSL_List L, int numprint);
//this function is useless, I wrote it only to see if the list is circular

#endif
