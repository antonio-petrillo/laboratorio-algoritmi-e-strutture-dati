#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "rbtree.h"

rb_node grandparent(rb_node node){
    assert(node != NULL);
    assert(node->parent != NULL);
    assert(node->parent->parent != NULL);
    return node->parent->parent;
}

rb_node sibling(rb_node node){
    assert(node != NULL);
    assert(node->parent != NULL);
    if(node == node->parent->left)
        return node->parent->right;
    else
        return node->parent->left;
}

rb_node uncle(rb_node node){
    assert(node != NULL);
    assert(node->parent != NULL);
    assert(node->parent->parent != NULL);
    return sibling(node->parent);
}

color_t node_color(rb_node node){
    return (node == NULL) ? BLACK : node->color;
}

int is_black(rb_node node){
    return (node == NULL) ? 1 : node->color == BLACK;
}

int is_red(rb_node node){
    return (node == NULL) ? 0 : node->color == RED;
}

int num_child(rb_node node){
    int num = 0;
    if(node->left != NULL) num++;
    if(node->right != NULL) num++;
    return num;
}

rbtree make_rbtree(){
    rbtree tree = (rbtree) malloc(sizeof(struct rbtree_t));
    assert(tree != NULL);
    tree->root = NULL;
    return tree;
}

rbtree drop_rbtree(rbtree tree){
    tree->root = drop_rbtree_helper(tree->root);
    free(tree);
    tree = NULL;
    return tree;
}


rb_node drop_rbtree_helper(rb_node node){
    if(node){
        drop_rbtree_helper(node->left);
        drop_rbtree_helper(node->right);
        delete_book(node->book);
        free(node);
    }
    return NULL;
}

rb_node make_rbnode(book_t book, unsigned int num_copies, color_t color, rb_node left, rb_node right){
    rb_node newnode = (rb_node) malloc(sizeof(struct rb_node_t));
    assert(newnode != NULL);
    newnode->left = left;
    newnode->right = right;
    newnode->book = book;
    newnode->num_copies = num_copies;
    newnode->parent = NULL;
    newnode->color = color;
    if(left != NULL) left->parent = newnode;
    if(right != NULL) right->parent = newnode;
    return newnode;
}

rb_node search_rb_node(rbtree tree, book_t book){
    rb_node ret_node = tree->root;
    int compare_result ;
    while(ret_node != NULL){
        compare_result = compare_by_ISBN(ret_node->book, book);
        if(compare_result > 0){
            ret_node = ret_node->left;
        }else if(compare_result < 0){
            ret_node = ret_node->right;
        }else{
            assert(compare_result == 0);
            return ret_node;
        }
    }
    return ret_node;
}

rb_node search_rb_node_from_node(rb_node node, book_t book){
    rb_node ret_node = node;
    int compare_result ;
    while(ret_node != NULL){
        compare_result = compare_by_ISBN(ret_node->book, book);
        if(compare_result > 0){
            ret_node = ret_node->left;
        }else if(compare_result < 0){
            ret_node = ret_node->right;
        }else{
            assert(compare_result == 0);
            return ret_node;
        }
    }
    return ret_node;
    
}

void rotate_left_rb(rbtree tree, rb_node node){
    rb_node newroot = node->right;
    replace_rb_node(tree, node, newroot);
    node->right = newroot->left;
    if(newroot->left){
        newroot->left->parent = node;
    }
    newroot->left = node;
    node->parent = newroot;
    return;
}

void rotate_right_rb(rbtree tree, rb_node node){
    rb_node newroot = node->left;
    replace_rb_node(tree, node, newroot);
    node->left = newroot->right;
    if(newroot->right){
        newroot->right->parent = node;
    }
    newroot->right = node;
    node->parent = newroot;
    return;
}

void replace_rb_node(rbtree tree, rb_node old_node, rb_node node){
    if(old_node->parent == NULL){
        tree->root = node;
    }else{
        if(old_node == old_node->parent->left){
            old_node->parent->left = node;
        }else{
            old_node->parent->right = node;
        }
        
    }
    if(node != NULL){
        node->parent = old_node->parent;
    }
    return;
}

void rbtree_insert(rbtree tree, book_t book, int num_copies){
    //rb_node newnode = make_rbnode(value, RED, NULL, NULL);
    rb_node newnode = NULL;
    int do_fixup = 0;
    int compare_result;
    if(tree->root == NULL){
        newnode = make_rbnode(book, num_copies, RED, NULL, NULL);
        tree->root = newnode;
        do_fixup = 1;
    }else{
        rb_node iter = tree->root;
        while(1){
            compare_result = compare_by_ISBN(iter->book, book);
            if(compare_result > 0){
                if(iter->left == NULL){
                    newnode = make_rbnode(book, num_copies, RED, NULL, NULL);
                    iter->left = newnode;
                    do_fixup = 1;
                    break;
                }else{
                    iter = iter->left;
                }
            }else if(compare_result < 0){
                if(iter->right == NULL){
                    newnode = make_rbnode(book, num_copies, RED, NULL, NULL);
                    iter->right = newnode;
                    do_fixup = 1;
                    break;
                }else{
                    iter = iter->right;
                }
            }else{
                iter->num_copies += num_copies;
                break;
            }
        }       
        if(do_fixup){
            newnode->parent = iter;
        }
    }
    if(do_fixup){
        rb_insert_fixup(tree, newnode);
    }
    return;
}

void rb_insert_fixup(rbtree tree, rb_node node){
    rb_node tmp = NULL;
    while(is_red(node->parent)){
        if(node->parent == node->parent->parent->left){//left violation
            tmp = uncle(node);
            if(is_red(tmp)){// uncle red
                node->parent->color = BLACK;
                tmp->color = BLACK;
                grandparent(node)->color = RED;
                node = grandparent(node);
            }
            else{ //uncle black
                if(node == node->parent->right){
                    node = node->parent;
                    rotate_left_rb(tree, node);
                }
                node->parent->color = BLACK;
                grandparent(node)->color = RED;
                rotate_right_rb(tree, grandparent(node));
            }
        }
        else{//right violation
            tmp = uncle(node);
            if(is_red(tmp)){//uncle red
                node->parent->color = BLACK;
                tmp->color = BLACK;
                grandparent(node)->color = RED;
                node = grandparent(node);
            }
            else{// uncle black
                if(node == node->parent->left){
                    node = node->parent;
                    rotate_right_rb(tree, node);
                }
                node->parent->color = BLACK;
                grandparent(node)->color = RED;
                rotate_left_rb(tree, grandparent(node));
            }
        }
    }
    tree->root->color = BLACK;
    return;
}


void rbtree_remove(rbtree tree, book_t book){
    rb_node del_node = search_rb_node(tree, book);
    rb_node child = NULL;
    if(del_node == NULL) return; // key not present into the tree
    if(num_child(del_node) == 2){
        rb_node predecessor = min_rb_from_node(del_node);
        delete_book(del_node->book);
        del_node->book = copy_book(predecessor->book);
        del_node->num_copies = predecessor->num_copies; 
        del_node = predecessor;
    }
    assert(del_node->left == NULL || del_node->right == NULL);
    child = (del_node->right == NULL) ? del_node->left : del_node->right;
    if(is_black(del_node)){
        del_node->color = node_color(child);
        delete_case1(tree, del_node);
    }
    replace_rb_node(tree, del_node, child);
    if(del_node->parent == NULL && child != NULL)
        child->color = BLACK;
    delete_book(del_node->book);
    free(del_node);
    return;
}

void rbtree_remove_with_addr(rbtree tree, rb_node key){
    rb_node del_node = key;
    rb_node child = NULL;
    if(del_node == NULL) return; // key not present into the tree
    if(num_child(del_node) == 2){
        rb_node predecessor = min_rb_from_node(del_node);
        delete_book(del_node->book);
        del_node->book = copy_book(predecessor->book);
        del_node->num_copies = predecessor->num_copies; 
        del_node = predecessor;
    }
    assert(del_node->left == NULL || del_node->right == NULL);
    child = (del_node->right == NULL) ? del_node->left : del_node->right;
    if(is_black(del_node)){
        del_node->color = node_color(child);
        delete_case1(tree, del_node);
    }
    replace_rb_node(tree, del_node, child);
    if(del_node->parent == NULL && child != NULL)
        child->color = BLACK;
    delete_book(del_node->book);
    free(del_node);
    return;
}

rb_node min_rb(rbtree tree){
    rb_node ret_node = tree->root;
    while(ret_node != NULL && ret_node->left != NULL) 
        ret_node = ret_node->left;
    return ret_node;
}

rb_node max_rb(rbtree tree){
    rb_node ret_node = tree->root;
    while(ret_node != NULL && ret_node->right != NULL)
        ret_node = ret_node->right;
    return ret_node;
}

rb_node min_rb_from_node(rb_node node){
    if(node && node->left == NULL) return node;
    return min_rb_from_node(node->left);
}

rb_node max_rb_from_node(rb_node node){
    if(node && node->right == NULL) return node;
    return max_rb_from_node(node->right);
}

void delete_case1(rbtree tree, rb_node node){
    if(node->parent != NULL){
        delete_case2(tree, node);
    }
    return;
}

void delete_case2(rbtree tree, rb_node node){
    if(is_red(sibling(node))){
        node->parent->color = RED;
        sibling(node)->color = BLACK;
        if(node == node->parent->left){
            rotate_left_rb(tree, node->parent);
        }
        else{
            rotate_right_rb(tree, node->parent);
        }
    }
    delete_case3(tree, node);
    return;
}

void delete_case3(rbtree tree, rb_node node){
    if(is_black(node->parent) && is_black(sibling(node)) && is_black(sibling(node)->left) && is_black(sibling(node)->right)){
        sibling(node)->color = RED;
        delete_case1(tree, node->parent);
    }else{
        delete_case4(tree, node);
    }
    return;
}

void delete_case4(rbtree tree, rb_node node){
    if(is_red(node->parent) && is_black(sibling(node)) && is_black(sibling(node)->left) && is_black(sibling(node)->right)){
        sibling(node)->color = RED;
        node->parent->color = BLACK;
    } 
    else{
        delete_case5(tree, node);
    }
    return;
}

void delete_case5(rbtree tree, rb_node node){
    if(node == node->parent->left && is_black(sibling(node)) && is_red(sibling(node)->left) && is_black(sibling(node)->right)){
        sibling(node)->color = RED;
        sibling(node)->left->color = BLACK;
        rotate_right_rb(tree, node);
    }
    else if(node == node->parent->right && is_black(sibling(node)) && is_red(sibling(node)->right) && is_black(sibling(node)->left)){
        sibling(node)->color = RED;
        sibling(node)->right->color = BLACK;
        rotate_left_rb(tree, node);
    }
    delete_case6(tree, node);
    return;
}

void delete_case6(rbtree tree, rb_node node){
    sibling(node)->color = node_color(node->parent);
    node->parent->color = BLACK;
    if(node == node->parent->left){
        assert(is_red(sibling(node)->right));
        sibling(node)->right->color = BLACK;
        rotate_left_rb(tree, node->parent);
    }
    else{
        assert(is_red(sibling(node)->left));
        sibling(node)->left->color = BLACK;
        rotate_right_rb(tree, node->parent);
    }
    return;
}

int is_empty_rb(rbtree tree){
    return tree->root == NULL;
}

book_t get_book_from_tree(rbtree tree, book_t book){
    book_t ret_book = NULL;
    rb_node tmp = search_rb_node(tree, book);
    if(tmp != NULL){
        if(tmp->num_copies > 0){
            tmp->num_copies--;
            ret_book = copy_book(tmp->book);
        }
        else{
            printf("there are no copies available for (isbn) %s\n", book->ISBN);
        }
    }   
    return ret_book; 
}