#ifndef CDL_LIST_H
#define CDL_LIST_H 1

#define HEAD 1
#define NOT_HEAD 0

//CSL :== Circular Single Linked 

typedef struct cdl_node{
	int value;
	unsigned int head_of_the_list : 1;
	struct cdl_node* next;
    struct cdl_node* prev;
}CDL_Node;

typedef CDL_Node* CDL_NodePtr;
typedef CDL_NodePtr CDL_List;

CDL_List makelist_cdl();
void cdl_error(char* message);
CDL_NodePtr makenode_cdl(int value);
CDL_List insert_in_head_cdl(CDL_List L, int value);
CDL_List insert_in_tail_cdl(CDL_List L, int value);
CDL_List insert_in_order_cdl(CDL_List L, int value);
CDL_List insert_node_in_head_cdl(CDL_List L, CDL_NodePtr node);
CDL_List insert_node_in_tail_cdl(CDL_List L, CDL_NodePtr node);
CDL_List insert_node_in_order_cdl(CDL_List L, CDL_NodePtr node);
CDL_List copy_cdl(const CDL_List L);
CDL_List order_cdl(CDL_List L);
CDL_List remove_duplicates_dl(CDL_List L);
void remove_with_key_cdl(CDL_List* L, int key);
const CDL_NodePtr min_cdl(const CDL_List L);
const CDL_NodePtr max_cdl(const CDL_List L);
unsigned int cdl_len(const CDL_List L);
int is_empty_cdl(const CDL_List L);
const CDL_NodePtr search_cdl(const CDL_List L, int value);
void print_cdl(const CDL_List L);
CDL_List drop_cdl(CDL_List L);

CDL_NodePtr cdl_union(const CDL_NodePtr L1, const CDL_NodePtr L2);
void cdl_union_rec(const CDL_NodePtr L1, const CDL_NodePtr L2, CDL_NodePtr* L3);
CDL_NodePtr cdl_intersect(const CDL_NodePtr L1, const CDL_NodePtr L2);
void cdl_intersect_rec(const CDL_NodePtr L1, const CDL_NodePtr L2, CDL_NodePtr* L3);
CDL_NodePtr cdl_difference(const CDL_NodePtr L1, const CDL_NodePtr L2);
void cdl_difference_rec(const CDL_NodePtr L1, const CDL_NodePtr L2, CDL_NodePtr* L3);

void multi_print_cdl(const CDL_List L, int numprint);
//this function is useless, I wrote it only to see if the list is circular

#endif