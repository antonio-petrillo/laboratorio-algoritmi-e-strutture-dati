#ifndef DL_LIST_H
#define DL_LIST_H 1

typedef struct dl_node{
    struct dl_node* next;
    struct dl_node* prev;
    int value;
}DL_Node;

typedef DL_Node* DL_NodePtr;
typedef DL_Node* DL_List;

DL_List makelist_dl();
void dl_error(char* message);
DL_NodePtr makenode_dl(int value);
DL_List insert_in_head_dl(DL_List L, int value);
DL_List insert_in_tail_dl(DL_List L, int value);
DL_List insert_in_order_dl(DL_List L, int value);
DL_List insert_node_in_head_dl(DL_List L, DL_NodePtr node);
DL_List insert_node_in_tail_dl(DL_List L, DL_NodePtr node);
DL_List insert_node_in_order_dl(DL_List L, DL_NodePtr node);
DL_List copy_dl(DL_List L);
DL_List order_dl(DL_List L);
DL_List remove_duplicates_dl(DL_List L);
void remove_with_key_dl(DL_List* L, int key);
const DL_NodePtr min_dl(const DL_List L);
const DL_NodePtr max_dl(const DL_List L);
unsigned int dl_len(const DL_List L);
int is_empty_dl(const DL_List L);
const DL_NodePtr search_dl(const DL_List L, int value);
void print_dl(const DL_List L);
DL_List drop_dl(DL_List L);

DL_NodePtr dl_union(const DL_NodePtr L1, const DL_NodePtr L2);
void dl_union_rec(const DL_NodePtr L1, const DL_NodePtr L2, DL_NodePtr* L3);
DL_NodePtr dl_intersect(const DL_NodePtr L1, const DL_NodePtr L2);
void dl_intersect_rec(const DL_NodePtr L1, const DL_NodePtr L2, DL_NodePtr* L3);
DL_NodePtr dl_difference(const DL_NodePtr L1, const DL_NodePtr L2);
void dl_difference_rec(const DL_NodePtr L1, const DL_NodePtr L2, DL_NodePtr* L3);

#endif