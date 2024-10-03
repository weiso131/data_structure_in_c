#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    char value;
    struct node *next;
    struct node *prev;
}Node;

Node* create_node(char value, Node* next, Node* prev) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = next;
    new_node->prev = prev;
    return new_node;
}

void show(Node **start) {
    

    while (*start != NULL) {
        printf("%c", (*start)->value);
        start = &(*start)->next;
    }
}


void delete(Node *trash) {
    if (trash->prev!= NULL) {
        trash->prev->next = trash->next;
    }
    if (trash->next!= NULL) {
        trash->next->prev = trash->prev;
    }
    free(trash);
}

int main() {
    Node *a = create_node('a', NULL, NULL);
    Node *b = create_node('b', NULL, a);
    Node *c = create_node('c', NULL, b);
    a->next = b;
    b->next = c;

    delete(b);
    show(&a);

    double n = 1 / ((double)2e0);
    printf("%.100f", n);


}