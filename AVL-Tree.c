#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INT_MAX 2147483647
#define INT_MIN -2147483648

int abs(int i) {
    if (i >= 0) { return i;  }
    else        { return -i; }
}

int max(int i, int j) {
    if (i < j) { return j; }
    else       { return i; }
}

// AVLnode Data Structure
struct AVLnode {
    int key;
    int height;
    struct AVLnode *left;
    struct AVLnode *right;
};

// allocates memory and creates an AVL node
struct AVLnode *nodeCreate(int key) {
    struct AVLnode *n = malloc(sizeof(struct AVLnode));
    n->key      = key;
    n->height   = 1;
    n->left     = NULL;
    n->right    = NULL;
    return n;
}

// destroys a node and all of it's children and free's their memory
void nodeDestroy(struct AVLnode *node) {
    if(node->left)  { nodeDestroy(node->left);  }
    if(node->right) { nodeDestroy(node->right); }
    free(node);
}

// finds the maximum node number
// returns INT_MIN if tree is NULL
int findMax(struct AVLnode *node) {
    if(node == NULL) { return INT_MIN; }

    struct AVLnode *temp = node;
    while(temp->right != NULL) { temp = temp->right; }
    return temp->key;
}

// finds the minimum node number
// returns INT_MAX if tree is NULL
int findMin(struct AVLnode *node) {
    if(node == NULL) { return INT_MAX; }

    struct AVLnode *temp = node;
    while(temp->left != NULL) { temp = temp->left; }
    return temp->key;
}

// updates the height of the current node
void updateheight(struct AVLnode *node) {
    int leftheight;
    int rightheight;

    if (node->left == NULL) { leftheight = 0; }
    else { leftheight = node->left->height; }

    if (node->right == NULL) { rightheight = 0; }
    else  { rightheight = node->right->height; }

    node->height = max(leftheight+1, rightheight+1);
}

// does a right rotation on a node 
// and returns a pointer to the new node at that position
struct AVLnode *rightRotation(struct AVLnode *node) {
    assert(node);
    assert(node->left);

    struct AVLnode *middle = node->left;
    struct AVLnode *left = node->left->left;
    struct AVLnode *right = node;
    struct AVLnode *rightleft = node->left->right;

    middle->left = left;
    middle->right = right;
    middle->right->left = rightleft;

    updateheight(left);
    updateheight(right);
    updateheight(middle);

    return middle;
}

// does a left rotation on a node 
// and returns a pointer to the new node at that position
struct AVLnode *leftRotation(struct AVLnode *node) {
    assert(node);
    assert(node->right);

    struct AVLnode *middle = node->right;
    struct AVLnode *left = node;
    struct AVLnode *right = node->right->right;
    struct AVLnode *leftright = node->right->left;

    middle->left = left;
    middle->right = right;
    middle->left->right = leftright;

    updateheight(left);
    updateheight(right);
    updateheight(middle);

    return middle;
}

// returns the balance of the node
int balance(struct AVLnode *node) {
    if(node == NULL) { return 0; }

    int leftheight;
    int rightheight;

    if (node->left == NULL) { leftheight = 0; }
    else { leftheight = node->left->height; }

    if (node->right == NULL) { rightheight = 0; }
    else  { rightheight = node->right->height; }
    
    return rightheight - leftheight;
}

// rebalances (i.e. perform rotations) parameter node
// depending on the blance factor (i.e. heights of it's children)
struct AVLnode *rebalance(struct AVLnode *node) {
    int midbalance = balance(node);
    int rightbalance = balance(node->right);
    int leftbalance = balance(node->left);

    // balanced
    if (abs(midbalance) < 2) { 
        return node;
    } // left-right rotation (LR) or "Double left"
    else if ( midbalance == 2 && rightbalance < 0) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    } // right-left rotation (RL) or "Double right" 
    else if (midbalance == -2 && leftbalance > 0) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    } // single left rotation
    else if (midbalance == 2) {
        return leftRotation(node);
    } // single right rotation {
    else if (midbalance == -2) {
        return  rightRotation(node);
    }

    //failsafe
    return NULL;
}

// Creates and inserts a new AVLnode with parameter key
// does nothing if the key already exists
struct AVLnode *insertNode(struct AVLnode *node, int key){
    if(node == NULL) {  return nodeCreate(key); 
    } else if(key > node->key) { 
        node->right = insertNode(node->right,key);
    } else if(key < node->key) {
        node->left = insertNode(node->left,key);
    }

    updateheight(node);
    return rebalance(node);
}

// searches for the node with parameter key
struct AVLnode *search(struct AVLnode *node, int key) {
    if (node == NULL)         { return NULL;                    }
    if (node->key == key)     { return node;                    }
    else if (node->key > key) { return search(node->right,key); }
    else if (node->key < key) { return search(node->left,key);  }
    else                      { return NULL;                    }
}

// Removes AVL node with the parameter key
struct AVLnode *removeNode(struct AVLnode *node, int key) {

    if (node == NULL) { return NULL; }

    if(node->key == key) {
        // case leaf node
        if (node->left == NULL && node->right == NULL) {
            nodeDestroy(node);
            return NULL;
        } 
        // case single right child
        else if (node->left == NULL) {
            struct AVLnode *returnNode = node->right;
            free(node);
            return returnNode;
        } 
        // case single left child
        else if (node->right == NULL) {
            struct AVLnode *returnNode = node->left;
            free(node);
            return returnNode;
        } 
        // case two children
        else {
            int replacement = findMin(node->right);
            node->key = replacement;
            node->right = removeNode(node->right,replacement);
        }
    } else if (node->key < key) {
        node->right = removeNode(node->right, key); 
    } else if (node->key > key) {
        node->left = removeNode(node->left, key);
    }

    updateheight(node);
    return rebalance(node);
}

struct AVLTree {
    struct AVLnode *root;
};

struct AVLTree *createTree(void) {
    struct AVLTree *t = malloc(sizeof(struct AVLTree));
    t->root = NULL;
    return t;
}

void destroyTree(struct AVLTree *t) {
    nodeDestroy(t->root);
    free(t);
}

void insert(struct AVLTree *t, int key) {
    t->root = insertNode(t->root, key);
}

// *note remove is already a declared function
void removee(struct AVLTree *t, int key) {
    t->root = removeNode(t->root, key);
}

// Recursive helper function for printTree
void printnode(struct AVLnode *node, int spaces) {
    for(int i = 0; i < spaces; ++i) {
        printf("  ");
    }
    printf("- %d\n", node->key);
    if(node->left) { printnode(node->left, spaces+1); }
    if(node->right) { printnode(node->right, spaces+1); }
}

// Prints the tree in a vertical and indented
// manner by doing an inorder traversal
void printTree(struct AVLTree *t) {
    printnode(t->root,0);
}


int main(void) {
    // testing here
    struct AVLTree *t = createTree();
    insert(t,1);
    insert(t,2);
    insert(t,3);
    printTree(t);

    destroyTree(t);
}


