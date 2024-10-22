#ifndef QUEUE_H  // 防止重複引用
#define QUEUE_H

#define QUEUE_VALUE_TYPE float

typedef struct queue_node {
    QUEUE_VALUE_TYPE value;
    struct queue_node *next;
}QueueNode;

typedef struct queue {
    QueueNode *front, *tail;
    void (*push)(struct queue*, QUEUE_VALUE_TYPE);
    void (*pop)(struct queue*);
    QUEUE_VALUE_TYPE (*get_front)(struct queue*);
}Queue;

QueueNode* createNode(QUEUE_VALUE_TYPE data);
Queue* createQueue();

#endif


