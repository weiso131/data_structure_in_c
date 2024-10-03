#include<stdlib.h>
#include<stdio.h>

typedef struct node {
    int value;
    struct node *child_left, *child_right, *mother;
}Node;

Node *create_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->child_left = NULL;
    node->child_right = NULL;
    node->mother = NULL;
}

typedef struct binary_search_tree {
    Node *root;
}BinarySearchTree;

BinarySearchTree* create_binary_search_tree() {
    BinarySearchTree *tree = malloc( sizeof( BinarySearchTree ) );
    tree->root = NULL;
}

void insert(BinarySearchTree *self, int value) {
    Node **insert_pos = &self->root;
    Node *new_node = create_node(value);

    while (*insert_pos != NULL) {
        if ((*insert_pos)->value > value) 
            insert_pos = &(*insert_pos)->child_left;
        else if ((*insert_pos)->value < value)
            insert_pos = &(*insert_pos)->child_right;
        else
            return;
    }
    *insert_pos = new_node;
}

Node** search(BinarySearchTree *self, int value) {
    Node **insert_pos = &self->root;
    Node *new_node = create_node(value);

    while (*insert_pos != NULL) {
        if ((*insert_pos)->value > value) 
            insert_pos = &(*insert_pos)->child_left;
        else if ((*insert_pos)->value < value)
            insert_pos = &(*insert_pos)->child_right;
        else
            return insert_pos;
    }
    return NULL;
}   

void delete(BinarySearchTree *self, int value) {
    Node **delete_pos = search(self, value);
    Node *trash = *delete_pos;
    if (*delete_pos == NULL)
        return;
    if ((*delete_pos)->child_left == NULL) {
        *delete_pos = (*delete_pos)->child_right;
    }
    else {
        Node **replacement = &(*delete_pos)->child_left;
        while ((*replacement)->child_right != NULL) 
            replacement = &(*replacement)->child_right;

        Node *replacement_node = *replacement;
        *replacement = NULL;
        replacement_node->child_left = (*delete_pos)->child_left;
        replacement_node->child_right = (*delete_pos)->child_right;
        *delete_pos = replacement_node;
        
    }
    free(trash);
    
}
void show(Node *node) {
    if (node != NULL) {
        printf("%d ", node->value);
        show(node->child_left);
        show(node->child_right);
    }
}

int main() {
    BinarySearchTree *tree = create_binary_search_tree();
    insert(tree, 30);
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 5);
    insert(tree, 40);
    insert(tree, 50);

    if (search(tree, 20) == NULL) {
        printf("20 Not Found\n");
    }
    if (search(tree, 60) == NULL) {
        printf("60 Not Found\n");
    }
    
    show(tree->root);
    printf("\n");
    delete(tree, 30);
    show(tree->root);

    return 0;
}