#include<stdlib.h>
#include<stdio.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define swap(a, b) {\
    int save = a;\
    a = b;\
    b = save;\
}

int abs(int a) {
    if (a < 0)
        return -a;
    return a;
}

typedef struct node {
    int value, height;
    struct node *child_left, *child_right, *mother;
}Node;

Node *create_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->height = 1;
    node->child_left = node->child_right = node->mother = NULL;
}

typedef struct binary_search_tree {
    Node *root;
}BinarySearchTree;

BinarySearchTree* create_binary_search_tree() {
    BinarySearchTree *tree = malloc( sizeof( BinarySearchTree ) );
    tree->root = NULL;
}


Node *__search_parent(BinarySearchTree *self, int value) {
    Node *current = self->root;
    while (1) {
        Node *child = NULL;
        if (current->value > value) 
            child = current->child_left;
        else 
            child = current->child_right;
        if (child == NULL || child->value == value) {
            return current;
        }
        current = child;

    }
}

void __update_height(Node *node) {
    int right = 0, left = 0;
    if (node->child_right != NULL) right = node->child_right->height;
    if (node->child_left != NULL) left = node->child_left->height;
    node->height = max(right, left) + 1;
}

int __get_bf(Node *node) {
    int right = 0, left = 0;
    if (node->child_right != NULL) right = node->child_right->height;
    if (node->child_left != NULL) left = node->child_left->height;
    return left - right;
}

#define __rotation_parent {\
    if (a->mother != NULL) {\
        b->mother = a->mother;\
        if (a->mother->value > a->value)\
            a->mother->child_left = b;\
        else\
            a->mother->child_right = b;\
    }\
    else {\
        tree->root = b;\
        b->mother = NULL;\
    }\
}

void __ll_rotation(Node *node, BinarySearchTree *tree) {
    
    Node *a = node, *b = a->child_left;
    Node *right1 = b->child_right;
    
    __rotation_parent;
    
    a->mother = b;
    b->child_right = a;
    a->child_left = right1;
    if (right1 != NULL) right1->mother = a;
    __update_height(a);
    __update_height(b);
}
void __rr_rotation(Node *node, BinarySearchTree *tree) {
    Node *a = node, *b = a->child_right;
    Node *left1 = b->child_left;
    
    __rotation_parent;
    a->mother = b;
    b->child_left = a;
    a->child_right = left1;
    if (left1 != NULL) left1->mother = a;
    __update_height(a);
    __update_height(b);
}

void __lr_rotation(Node *node, BinarySearchTree *tree) {
    Node *a = node, *b = a->child_left;
    __rr_rotation(b, tree);
    __ll_rotation(a, tree);
}
void __rl_rotation(Node *node, BinarySearchTree *tree) {
    Node *a = node, *b = a->child_right;
    __ll_rotation(b, tree);
    __rr_rotation(a, tree);
}
void __rotation(Node *node, int bf, BinarySearchTree *tree) {
    int first_child = (bf == -2), second_child = 0;
    Node *first_node = node->child_left;
    if (first_child)//走右邊
        first_node = node->child_right;
    if ((first_node->child_left == NULL) || (first_node->child_right != NULL && \
    first_node->child_right > first_node->child_left))
        second_child = 1;


    if (first_child == 0 && second_child == 0) //LL 
        __ll_rotation(node, tree);
        
    else if (first_child == 1 && second_child == 1) {//RR 
        printf("test\n");
        __rr_rotation(node, tree);
        
    }
    else if (first_child == 1 && second_child == 0) //RL
        __rl_rotation(node, tree);
    else //LR
        __lr_rotation(node, tree);
}

void __maintain(BinarySearchTree *self, Node *node) {

    while (node->mother != NULL) {
        node = node->mother;
        int bf = __get_bf(node);
        if (abs(bf) < 2) {
            int old_height = node->height;
            __update_height(node);
            if (old_height == node->height) break;
        }
        else {
            __rotation(node, bf, self);
        }
    }

}


void insert(BinarySearchTree *self, int value) {
    Node *new_node = create_node(value);
    if (self->root == NULL) {
        self->root = new_node;
        return;
    }
    Node *parent = __search_parent(self, value);

    if (parent->value < value) 
        parent->child_right = new_node;
    else
        parent->child_left = new_node;
    new_node->mother = parent;
    __maintain(self, new_node);
    
}

Node* search(BinarySearchTree *self, int value) {
    if (self->root->value == value) 
        return self->root;
    Node *parent = __search_parent(self, value);
    if (parent->value < value) 
        return parent->child_right;
    else
        return parent->child_left;
}   

Node *__find_replacement(Node *target) {
    Node *replacement = NULL;
    if (target->child_left != NULL) {
        replacement = target->child_left;
        while (replacement->child_right != NULL)
            replacement = replacement->child_right;
    }
    else if (target->child_right != NULL) {
        replacement = target->child_right;
        while (replacement->child_left != NULL)
            replacement = replacement->child_left;
    }
    return replacement;
}

void __kill_child(Node *target) {
    if (target->mother != NULL) {
        if (target->mother->value > target->value) 
            target->mother->child_left = NULL;
        else
            target->mother->child_right = NULL;
    }
    
}


void delete(BinarySearchTree *self, int value) {
    Node *target = search(self, value);
    Node *replacement = __find_replacement(target);

    if (replacement != NULL) {
        int save = replacement->value;
        Node *maintain_target = replacement->mother;
        __kill_child(replacement);
        swap(replacement->value, target->value);
        __maintain(self, replacement);
        free(replacement);
    }
    else {

        target->height = 0;
        __maintain(self, target);
        __kill_child(target);
        free(target);
    } 
}

void show(Node *node, int rank) {
    if (node != NULL) {
        printf("%d: %d %d\n", rank, node->value, node->height);
        show(node->child_left, rank + 1);
        show(node->child_right, rank + 1);
        
    }
}

int main() {
    BinarySearchTree *tree = create_binary_search_tree();
    insert(tree, 33);
    insert(tree, 13);
    insert(tree, 53);
    insert(tree, 9);
    insert(tree, 21);
    insert(tree, 61);
    insert(tree, 8);
    insert(tree, 11);
    delete(tree, 13);

    show(tree->root, 0);

    return 0;
}

