#include <stdio.h>
#include <stdlib.h>



struct AVLnode {
    int key;
    int height;
    struct AVLnode *left;
    struct AVLnode *right;
};

// allocates memory and creates an AVL node
struct nodeCreate(int key) {
    struct AVLnode *n = malloc(sizeof(struct AVLnode));
    n->key = key;
    n->height = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// destroys a node and all of it's children and free's their memory
struct nodeDestroy(struct AVLnode *node) {
    if(node->left) { nodeDestroy(node->left); }
    if(node->right) { nodeDestroy(node-right); }
    free(node);
}

void rightRotation(struct AVLnode *node) {
    //to do
}

void leftRotation(struct AVLnode *node) {
    //to do
}

void insertNode(struct AVLnode *node){
    //to do
}

void rebalance(struct ALVnode *node) {
    //to do
}

struct AVLTree {
    struct AVLnode *root;
}

int main(void) {
    // testing here

}


