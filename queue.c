#include<stdlib.h>
#include<stdio.h>
#include "queue.h"



QueueNode* createNode(QUEUE_VALUE_TYPE data) {
    QueueNode *node = malloc(sizeof(QueueNode));
    node->value = data;
    node->next = NULL;
    return node;
}




void push(Queue *self, QUEUE_VALUE_TYPE value) {
    QueueNode *new_node = createNode(value);
    self->tail->next = new_node;
    self->tail = new_node;
}
void pop(Queue *self) {
    QueueNode *trash = self->front->next;
    self->front->next = trash->next;
    free(trash);
}

QUEUE_VALUE_TYPE get_front(Queue *self) {
    return self->front->next->value;
}

Queue* createQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->front = malloc(sizeof(QueueNode));
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

