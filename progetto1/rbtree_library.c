#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "rbtree_library.h"

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
    assert(tree == NULL);
    return tree;
}


rb_node drop_rbtree_helper(rb_node node){
    if(node){
        drop_rbtree_helper(node->left);
        drop_rbtree_helper(node->right);
        drop_booklist(node->booklist);
        free(node);
    }
    return NULL;
}

rb_node make_rbnode(book_t new_book, color_t color, rb_node left, rb_node right){
    rb_node newnode = (rb_node) malloc(sizeof(struct rb_node_t));
    assert(newnode != NULL);
    newnode->left = left;
    newnode->right = right;
    newnode->parent = NULL;
    newnode->color = color;
    strcpy(newnode->ISBN, new_book->ISBN);
    newnode->booklist = make_booklist();
    booklist_push(newnode->booklist, new_book);
    if(left != NULL) left->parent = newnode;
    if(right != NULL) right->parent = newnode;
    return newnode;
}

rb_node search_rb_node(rbtree tree, book_t book){
    rb_node ret_node = tree->root;
    while(ret_node != NULL){
        int compare_result = compare_ISBN(ret_node->ISBN, book->ISBN);
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
    while (ret_node != NULL){
        int compare_result = compare_ISBN(node->ISBN, book->ISBN);
        if(compare_result > 0){
            ret_node = ret_node->left;
        }
        else if(compare_result < 0){
            ret_node = ret_node->right;
        }
        else{
            assert(compare_result == 0);
            return ret_node;
        }
    }
    return ret_node;
}

booklist_t search_booklist_in_rbtree(rbtree tree, book_t book){
    rb_node ret_node = tree->root;
    while(ret_node != NULL){
        int compare_result = compare_ISBN(ret_node->ISBN, book->ISBN);
        if(compare_result > 0){
            ret_node = ret_node->left;
        }else if(compare_result < 0){
            ret_node = ret_node->right;
        }else{
            assert(compare_result == 0);
            return ret_node->booklist;
        }
    }
    return NULL;
}

booklist_t search_booklist_in_rbtree_from_node(rb_node node, book_t book){
    rb_node ret_node = node;
    while (ret_node != NULL){
        int compare_result = compare_ISBN(node->ISBN, book->ISBN);
        if(compare_result > 0){
            ret_node = ret_node->left;
        }
        else if(compare_result < 0){
            ret_node = ret_node->right;
        }
        else{
            assert(compare_result == 0);
            return ret_node->booklist;
        }
    }
    return NULL;
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

void rbtree_insert(rbtree tree, book_t book){
    rb_node newnode = NULL;//make_rbnode(book, RED, NULL, NULL);
    int do_fixup = 0;
    if(tree->root == NULL){
        do_fixup = 1;
        newnode = make_rbnode(book, RED, NULL, NULL);
        tree->root = newnode;
    }else{
        rb_node iter = tree->root;
        int compare_result;
        while(1){
            compare_result = compare_ISBN(iter->ISBN, book->ISBN);
            if(compare_result > 0){
                if(iter->left == NULL){
                    newnode = make_rbnode(book, RED, NULL, NULL);
                    iter->left = newnode;
                    do_fixup = 1;
                    break;
                }else{
                    iter = iter->left;
                }
            }else if(compare_result < 0){
                if(iter->right == NULL){
                    newnode = make_rbnode(book, RED, NULL, NULL);
                    iter->right = newnode;
                    do_fixup = 1;
                    break;
                }else{
                    iter = iter->right;
                }
            }else{
                assert(compare_result == 0);
                booklist_push(iter->booklist, book);
                break;
            }
        }       
        if(do_fixup) {
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
        drop_booklist(del_node->booklist);
        strcpy(del_node->ISBN, predecessor->ISBN);
        drop_booklist(del_node->booklist);
        copy_booklist(del_node->booklist, predecessor->booklist);
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
    drop_booklist(del_node->booklist);
    free(del_node);
    return;
}

void rbtree_remove_with_addr(rbtree tree, rb_node key){
    rb_node del_node = key;
    rb_node child = NULL;
    if(del_node == NULL) return; // key not present into the tree
    if(num_child(del_node) == 2){
        rb_node predecessor = min_rb_from_node(del_node);
        drop_booklist(del_node->booklist);
        strcpy(del_node->ISBN, predecessor->ISBN);
        drop_booklist(del_node->booklist);
        copy_booklist(del_node->booklist, predecessor->booklist);
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
    drop_booklist(del_node->booklist);
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

void print_rbnode_booklist(rb_node node){
    int num_copy = booklist_size(node->booklist);
    printf("########### BOOK INFO ##############\n");
        printf("TITLE: %s\n", node->booklist->head->book->title);
        printf("ISBN: %s\n", node->booklist->head->book->ISBN);
        printf("%s:--%s\n", ((node->booklist->head->book->num_authors == 1) ? "AUTHOR" : "AUTHORS"), node->booklist->head->book->authors[0]);
        for(unsigned int i=1; i < node->booklist->head->book->num_authors; i++){
            printf("        |-%s\n", node->booklist->head->book->authors[i]);
        }
        printf("PRICE: %.2lf\n", node->booklist->head->book->price);
        printf("COPIES AVAILABLE: %d\n", num_copy);
        printf("####################################\n\n");
    return;
}

void in_order_visit_rb(rbtree tree){
    puts("In order visit library\n");
    in_order_visit_rb_helper(tree->root);
    puts("");
    return;
}

void pre_order_visit_rb(rbtree tree){
    puts("Pre order visit library\n");
    pre_order_visit_rb_helper(tree->root);
    puts("");
    return;
}

void post_order_visit_rb(rbtree tree){
    puts("Post order visit library\n");
    post_order_visit_rb_helper(tree->root);
    puts("");
    return;
}

void in_order_visit_rb_helper(rb_node node){
    if(node){
        in_order_visit_rb_helper(node->left);
        print_rbnode_booklist(node);
        in_order_visit_rb_helper(node->right);
    }
    return;
}

void pre_order_visit_rb_helper(rb_node node){
    if(node){
        print_rbnode_booklist(node);
        pre_order_visit_rb_helper(node->left);
        pre_order_visit_rb_helper(node->right);
    }
    return;
}

void post_order_visit_rb_helper(rb_node node){
    if(node){
        post_order_visit_rb_helper(node->left);
        post_order_visit_rb_helper(node->right);
        print_rbnode_booklist(node);
    }
    return;
}

void load_library(rbtree tree, FILE* stream){
    printf("test");
    assert(stream != NULL);
    printf("test");
    char buffer_ISBN[14];
    char buffer_title[256];
    unsigned int buffer_num_authors;
    char** buffer_authors;
    char buffer_author[256];
    double buffer_price;
    unsigned int buffer_num_copies = 0;
    while(fscanf(stream, "%s", buffer_ISBN) > 0){
        printf("test");
        fscanf(stream, "%[^\n]%*c", buffer_title);
        fscanf(stream, "%u", &buffer_num_authors);
        buffer_authors = (char**) calloc(buffer_num_authors, sizeof(char*));
        assert(buffer_authors != NULL);
        for(unsigned int i=0; i < buffer_num_authors; i++){
            fscanf(stream, "%[^\n]%*c", buffer_author);
            buffer_authors[i] = (char*) calloc(strlen(buffer_author) + 1, sizeof(char));
            assert(buffer_authors[i] != NULL);
            strcpy(buffer_authors[i], buffer_author);
        }
        fscanf(stream, "%lf", &buffer_price);
        fscanf(stream, "%u", &buffer_num_copies);
        for(unsigned int i=0; i<buffer_num_copies; i++){
            rbtree_insert(tree, make_book(buffer_ISBN, buffer_title, buffer_authors, buffer_num_authors, buffer_price));
        }
        for(unsigned int i=0; i < buffer_num_authors; i++){
            free(buffer_authors[i]);
        }
        free(buffer_authors);
    }
    return;
}

void store_library(rbtree tree, FILE* stream){
    assert(stream != NULL);
    store_library_helper(tree->root, stream);
    return;
}

void store_library_helper(rb_node node, FILE* stream){
    if(node){
        unsigned int num_author = node->booklist->head->book->num_authors;
        fprintf(stream, "%s\n", node->booklist->head->book->ISBN);//isbn
        fprintf(stream, "%s\n", node->booklist->head->book->title);//title
        fprintf(stream, "%u\n", num_author);// num_author
        for(int i=0; i<num_author; i++){
            fprintf(stream, "%s\n", node->booklist->head->book->authors[i]); //author line by line
        }
        fprintf(stream, "%lf", node->booklist->head->book->price);//price
        fprintf(stream, "%u", booklist_size(node->booklist));//num of copies
    }
}