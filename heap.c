#include<stdio.h>
#include<stdlib.h>
#include "heap.h"

HeapNode *create_node(HEAP_VALUE_TYPE value, char is_root) {
    HeapNode *node = malloc(sizeof(HeapNode));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    node->is_root = is_root;
    return node;
}

Heap *create_heap() {
    Heap *heap = malloc(sizeof(Heap));
    heap->root = create_node(0, 1);
    heap->node_count = 0;
    return heap;
}

void swap(HEAP_VALUE_TYPE *a, HEAP_VALUE_TYPE *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void get_last_node(Heap *heap, HeapNode **parent, char *last_bit) {
    int node_count = heap->node_count + 1;
    char first = 0;
    HeapNode **current = &(heap->root);
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

void insert_node(Heap *heap, HEAP_VALUE_TYPE value) {
    HeapNode *new_node = create_node(value, 0);
    HeapNode *parent = NULL;
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
void delete_node(Heap *heap) {
    HeapNode *top = heap->root->right;
    HeapNode *last_parent = NULL, *last_node = NULL;
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
        HeapNode *child = (top->right->value < top->left->value)? top->right : top->left;
        swap(&top->value, &child->value);
        top = child;
    }
    if (top->right != NULL && top->right->value < top->value)
        swap(&top->value, &top->right->value);

}









int main() {
    Heap *heap = create_heap();
    insert_node(heap, 10);
    insert_node(heap, 6);
    insert_node(heap, 4);
    insert_node(heap, 3);
    insert_node(heap, 2);
    delete_node(heap);
    delete_node(heap);
    delete_node(heap);
    printf("heap top: %d\n", heap->root->right->value);
}
