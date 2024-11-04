#ifndef HEAP_H  // 防止重複引用
#define HEAP_H

#define HEAP_VALUE_TYPE int

typedef struct node {
    struct node *left, *right, *parent;
    HEAP_VALUE_TYPE value;
    char is_root;
}HeapNode;

HeapNode *create_node(HEAP_VALUE_TYPE value, char is_root);

typedef struct heap {
    HeapNode *root;
    int node_count;
}Heap;

Heap *create_heap();
void get_last_node(Heap *heap, HeapNode **parent, char *last_bit);

void insert_node(Heap *heap, HEAP_VALUE_TYPE value);

void delete_node(Heap *heap);

#endif


