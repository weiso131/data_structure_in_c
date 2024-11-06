#include<stdio.h>
#include<stdlib.h>

typedef struct edge {
    int length;
    int start, end;
}Edge;

Edge *create_edge(int start, int end, int length) {
    Edge *edge = malloc(sizeof(edge));
    edge->start = start;
    edge->end = end;
    edge->length = length;

    return edge;
}

#define DIS_VALUE_TYPE int

typedef struct dis_node {
    DIS_VALUE_TYPE value;
    struct dis_node *parent;
}DisNode;

DisNode *create_dis_node(DIS_VALUE_TYPE value) {
    DisNode *node = malloc(sizeof(DisNode));
    node->value = value;
    node->parent = NULL;
    return node;
}

DisNode *find_top_parent(DisNode *now) {
    if (now->parent == NULL)
        return now;
    now->parent = find_top_parent(now->parent);
    return now->parent;
}

#define HEAP_VALUE Edge*

typedef struct heap_node {
    HEAP_VALUE value;
    struct heap_node *left, *right, *parent;
}HeapNode;

HeapNode *create_heap_node(HEAP_VALUE value) {
    HeapNode *node = malloc(sizeof(HeapNode));
    node->value = value;
    node->left = node->right = node->parent = NULL;
    return node;
}

typedef struct heap {
    HeapNode *root;
    int value_num;
}Heap;

Heap *create_heap() {
    Heap *heap = malloc(sizeof(Heap));
    heap->root = create_heap_node(0);
    heap->value_num = 0;
}

HeapNode *get_last(Heap *heap) {
    int num = heap->value_num;
    char find_first_1 = 0;
    HeapNode *last_parent = heap->root;
    for (int i = 31;i > 0;i--) {
        if ((num >> i) & 1)
            find_first_1 = 1;
        if (find_first_1) {
            
            if ((num >> i) & 1 == 1) 
                last_parent = last_parent->right;
            else
                last_parent = last_parent->left;
        }
    }
    return last_parent;
}

void swap(HEAP_VALUE* a, HEAP_VALUE* b) {
    HEAP_VALUE save = *a;
    *a = *b;
    *b = save;
}

char greater(Edge *a, Edge *b) {
    return a->length < b->length;
}

void insert(Heap *self, HEAP_VALUE value) {
    self->value_num += 1;
    HeapNode *new_node = create_heap_node(value);
    HeapNode *parent = get_last(self);
    new_node->parent = parent;
    if (self->value_num & 1) 
        parent->right = new_node;
    else
        parent->left = new_node;
    
    while (new_node->parent->parent != NULL && greater(new_node->value, new_node->parent->value)) {
        swap(&(new_node->value), &(new_node->parent->value));
        new_node = new_node->parent;
    }
}

void delete(Heap *self) {
    HeapNode *top = self->root->right;
    HeapNode *last_parent = get_last(self);
    HeapNode *last = NULL;
    if (self->value_num & 1) {
        last = last_parent->right;
        last_parent->right = NULL;
    } 
    else {
        last = last_parent->left;
        last_parent->left = NULL;
    }
        
    self->value_num--;
    swap(&(last->value), &(top->value));
    free(last);


    while (((top->left != NULL && greater(top->left->value, top->value)) || 
    (top->right != NULL && greater(top->right->value, top->value)))) {
        HeapNode *swap_node = top->right;
        if (top->right == NULL || (top->left != NULL && greater(top->left->value, top->right->value)))
            swap_node = top->left;
        swap(&(swap_node->value), &(top->value));
        top = swap_node;
        
    }

}






int main() {
    
    int n, m;
    scanf("%d%d", &n, &m);
    int complete_node = 0;
    int *array = calloc(n, sizeof(int));
    Heap *heap = create_heap();
    DisNode **dis_array = (DisNode **)malloc(sizeof(DisNode*) * n);
    for (int i = 0;i < n;i++)
        dis_array[i] = create_dis_node(i);

    for (int i = 0;i < m;i++) {
        int a, b, l;
        scanf("%d%d%d", &a, &b, &l);
        insert(heap, create_edge(a, b, l));
    }


    for (int i = 0;i < m;i++) {
        Edge *edge = heap->root->right->value;
        delete(heap);
        DisNode *a_parent = find_top_parent(dis_array[edge->start - 1]), *b_parent = find_top_parent(dis_array[edge->end - 1]);

        if (a_parent != b_parent) {
            b_parent->parent = a_parent;
            printf("%d %d\n", edge->start, edge->end);
        }

    }
        


}
