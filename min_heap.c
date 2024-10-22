#include<stdio.h>
#include<stdlib.h>

#define VALUE_TYPE int

typedef struct node {
    struct node *left, *right, *parent;
    VALUE_TYPE value;
    char is_root;
}Node;

Node *create_node(VALUE_TYPE value, char is_root) {
    Node *node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    node->is_root = is_root;
    return node;
}


typedef struct heap {
    Node *root;
    int node_count;
}Heap;

Heap *create_heap() {
    Heap *heap = malloc(sizeof(Heap));
    heap->root = create_node(0, 1);
    heap->node_count = 0;
    return heap;
}

void swap(VALUE_TYPE *a, VALUE_TYPE *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void get_last_node(Heap *heap, Node **parent, char *last_bit) {
    int node_count = heap->node_count + 1;
    char first = 0;
    Node **current = &(heap->root);
    for (int i = 31;i >= 0;i--) {
        char bit = (node_count >> i) & 1;
        if (bit) first = 1;

        if (first) {
            *parent = *current;
            *last_bit = bit;
            if (bit) 
                current = &((*current)->right);
            else 
                current = &((*current)->left);
        }
            
    }
}

void insert(Heap *heap, VALUE_TYPE value) {
    Node *new_node = create_node(value, 0);
    Node *parent = NULL;
    char last_bit = 0;
    get_last_node(heap, &parent, &last_bit);
    heap->node_count++;
    new_node->parent = parent;
    if (last_bit)
        parent->right = new_node;
    else
        parent->left = new_node;

    while (parent->value > new_node->value && !parent->is_root) {
        swap(&parent->value, &new_node->value);
        new_node = parent;
        parent = parent->parent;
    }

    
}
void delete(Heap *heap) {
    Node *top = heap->root->right;
    Node *last_parent = NULL, *last_node = NULL;
    char last_bit = 0;
    heap->node_count--;
    get_last_node(heap, &last_parent, &last_bit);
    if (last_bit) {
        last_node = last_parent->right;
        last_parent->right = NULL;
    }
    else {
        last_node = last_parent->left;
        last_parent->left = NULL;
    }
        
    
    swap(&top->value, &last_node->value);
    free(last_node);

    while (top->right != NULL && top->left != NULL && (top->value > top->right->value || top->value > top->left->value)) {
        Node *child = (top->right->value < top->left->value)? top->right : top->left;
        swap(&top->value, &child->value);
        top = child;
    }
    if (top->right != NULL && top->right->value < top->value)
        swap(&top->value, &top->right->value);

}









int main() {
    Heap *heap = create_heap();
    insert(heap, 10);
    insert(heap, 6);
    insert(heap, 4);
    insert(heap, 3);
    insert(heap, 2);
    delete(heap);
    delete(heap);
    delete(heap);
    printf("heap top: %d\n", heap->root->right->value);
}
