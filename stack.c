#include <stdio.h>
#include <stdlib.h>

#define STACK_TYPE int
typedef struct stack_node {
    STACK_TYPE value;
    struct stack_node *next;
}StackNode;

StackNode* create_node(STACK_TYPE value, StackNode* next) {
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    new_node->value = value;
    new_node->next = next;
    return new_node;
}

typedef struct stack {
    StackNode* top;
    int size;
    void (*push)(struct stack*, STACK_TYPE);
    void (*pop)(struct stack*);
    STACK_TYPE (*get_top)(struct stack*);
}Stack;

void push(Stack* self, STACK_TYPE value) {
    StackNode *new_node = create_node(value, self->top);
    self->top = new_node;
    self->size++;
}

void pop(Stack* self) {
    StackNode *trash = self->top;
    self->top = (self->top)->next;
    self->size--;
    free(trash);
}

STACK_TYPE get_top(Stack* self) {
    return self->top->value;
}

Stack* create_stack() {
    StackNode* top = NULL;
    Stack* new_stack = (Stack*)malloc(sizeof(Stack));
    *new_stack = (Stack){top, 0, &push, &pop, &get_top};

    return new_stack;
}



int main() {
    int n = 7;
    char tree[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char check[7]= {0, 0, 0, 0, 0, 0, 0};


    Stack *stack = create_stack();

    stack->push(stack, 1);

    while (stack->size != 0) {
        int save = stack->get_top(stack);
        if (save * 2 <= n && check[save * 2 - 1] == 0) {
            if (save * 2 + 1 <= n && check[save * 2] == 0) {
                stack->push(stack, save * 2 + 1);
            }
            stack->push(stack, save * 2);
        }
        else {
            printf("%c ", tree[save - 1]);
            stack->pop(stack);
            check[save - 1] = 1;
            
        }
        
    }

}
