#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    struct node* left;
    struct node* right;
    char* str;
}Node;

typedef Node* NodePtr;
typedef Node* Tree;

void error(char* message);
Tree makeTree();
NodePtr makenode(char* str);
Tree insert(Tree tree, char* str);
Tree drop(Tree tree);
void inOrder(Tree tree);

Tree delNode(Tree tree, char* key);
NodePtr deleteRoot(NodePtr node);
NodePtr minDeconnection(NodePtr child, NodePtr parent);

Tree esercizio3(Tree tree, char c1, char c2);
int numOccorrenze(char* str, char key);

int main(int argc, char** argv){
    Tree tree = makeTree();
    FILE* fp = fopen(argv[1], "r");
    if(!fp) error("error fopen returned NULL");
    char buffer[256];
    while (fscanf(fp, "%s", buffer) > 0){
        tree = insert(tree, buffer);
    }
    printf("stampa dell'albero prima dell'esercizio\n");
    inOrder(tree);
    tree = esercizio3(tree, argv[2][0], argv[3][0]);
    //tree = delNode(tree, "murakami"); test di del node 
    printf("\nstampa dell'albero dopo l'esercizio\n");
    inOrder(tree);
    tree = drop(tree);
    fclose(fp);
    return 0;
}

void error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

Tree makeTree(){
    return NULL;
}

NodePtr makenode(char* str){
    NodePtr newnode = (NodePtr) malloc(sizeof(Node));
    if(!newnode) error("error in function makenode, no memory available for thr node");
    newnode->left = newnode->right = NULL;
    newnode->str = (char*) calloc(strlen(str)+1, sizeof(char));
    if(!newnode->str) error("error in function makenode, no memory available for thr string");
    strcpy(newnode->str, str);
    return newnode;
}

Tree insert(Tree tree, char* str){
    if(!tree) tree = makenode(str);
    else{
        if(strcmp(tree->str, str) > 0){
            tree->left = insert(tree->left, str);
        }else{
            tree->right = insert(tree->right, str);
        }
    }
    return tree;
}

void inOrder(Tree tree){
    if(tree){
        inOrder(tree->left);
        printf("stringa del nodo: %s\n", tree->str);
        inOrder(tree->right);
    }
    return;
}

Tree drop(Tree tree){
    if(tree){
        tree->left = drop(tree->left);
        tree->right = drop(tree->right);
        free(tree->str);
        free(tree);
    }
    return NULL;
}

Tree delNode(Tree tree, char* key){
    if(tree){
        if(strcmp(tree->str, key) > 0){
            tree->left = delNode(tree->left, key);
        }else if(strcmp(tree->str, key) < 0){
            tree->right = delNode(tree->right, key);
        }else{
            if(!(tree->left && tree->right)){
                tree = deleteRoot(tree);
            }else{
                NodePtr min = minDeconnection(tree->right, tree);
                free(tree->str);
                tree->str = (char*) realloc(tree->str, strlen(min->str)+1);
                if(!tree->str) error("error in function delNode: no memory available for the realloc");
                strcpy(tree->str, min->str);
                free(min->str);
                free(min);
            }
        }
    }
    return tree;
}

NodePtr deleteRoot(NodePtr node){
    NodePtr tmp = node;
    if(node->left){
        node = node->left;
    }else{
        node = node->right;
    }
    free(tmp->str);
    free(tmp);
    return node;
}

NodePtr minDeconnection(NodePtr child, NodePtr parent){
    NodePtr retNode = NULL;
    if(child->left){
        retNode = minDeconnection(child->left, child);
    }
    else{
        retNode = child;
        if(child == parent->left) parent->left = child->right;
        else parent->right = child->right;
    }
    return retNode;
}

Tree esercizio3(Tree tree, char c1, char c2){
    if(tree){
        tree->left = esercizio3(tree->left, c1, c2);
        tree->right = esercizio3(tree->right, c1, c2);
        if(tree->str[0] == c1 && numOccorrenze(tree->str, c2) >= 2) tree = delNode(tree, tree->str);
    }
    return tree;
}

int numOccorrenze(char* str, char key){
    int numOccorrenze = 0;
    int index = 0;
    while(str[index] != '\0'){
        if(key == str[index]) numOccorrenze++;
        index++;
    }
    return numOccorrenze;
}