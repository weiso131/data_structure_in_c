#include<stdlib.h>
#include<stdio.h>

typedef struct node {
    int value;
    struct node *next;
}Node;

Node* createNode(int data) {
    Node *node = malloc(sizeof(Node));
    node->value = data;
    node->next = NULL;
    return node;
}


typedef struct queue {
    Node *front, *tail;
    void (*push)(struct queue*, int);
    void (*pop)(struct queue*);
    int (*get_front)(struct queue*);
}Queue;

void push(Queue *self, int value) {
    Node *new_node = createNode(value);
    self->tail->next = new_node;
    self->tail = new_node;
}
void pop(Queue *self) {
    Node *trash = self->front->next;
    self->front->next = trash->next;
    free(trash);
}

int get_front(Queue *self) {
    return self->front->next->value;
}

Queue* createQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->front = malloc(sizeof(Node));
    queue->front->next = NULL;
    queue->tail = queue->front;
    
    queue->push = &push;
    queue->pop = &pop;
    queue->get_front = &get_front;
    return queue;
}



int main() {
    Queue *queue = createQueue();
    push(queue, 1);
    push(queue, 2);
    push(queue, 3);

    for (int i = 0;i < 3;i++) {
        printf("%d", queue->get_front(queue));
        queue->pop(queue);

    }
    

    return 0;
}

