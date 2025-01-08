#include<stdlib.h>
#include<stdio.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define swap(a, b) {\
    int save = a;\
    a = b;\
    b = save;\
}

int abs(int a) {
    if (a < 0)
        return -a;
    return a;
}

typedef struct node {
    int value, height;
    struct node *mother;
    struct node **children;
}Node;

Node *create_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->height = 1;
    node->mother = NULL;
    node->children = (Node**)malloc(sizeof(Node*) * 2);
    return node;
}

typedef struct binary_search_tree {
    Node *root;
}BinarySearchTree;

BinarySearchTree* create_binary_search_tree() {
    BinarySearchTree *tree = malloc( sizeof( BinarySearchTree ) );
    tree->root = NULL;
    return tree;
}
Node *__search_parent(BinarySearchTree *self, int value) {
    Node *current = self->root;
    while (1) {
        Node *child = current->children[value > current->value];
        if (child == NULL || child->value == value) 
            return current;
        current = child;
    }
    return current;
}

void __update_height(Node *node) {
    int right = 0, left = 0;
    if (node->children[1] != NULL) right = node->children[1]->height;
    if (node->children[0] != NULL) left = node->children[0]->height;
    node->height = max(right, left) + 1;
}

int __get_bf(Node *node) {
    int right = 0, left = 0;
    if (node->children[1] != NULL) right = node->children[1]->height;
    if (node->children[0] != NULL) left = node->children[0]->height;
    return left - right;
}

void __rotation_base(Node *node, BinarySearchTree *tree, char ll) {
    Node *a = node, *b = a->children[!ll];
    Node *move_child = b->children[ll];
    if (a->mother != NULL) {
        b->mother = a->mother;
        a->mother->children[a->mother->value < a->value] = b;
    }
    else {
        tree->root = b;
        b->mother = NULL;
    }
    a->mother = b;
    b->children[ll] = a;
    a->children[!ll] = move_child;
    if (move_child != NULL) move_child->mother = a;
    __update_height(a);
    __update_height(b);
}

void __ll_rotation(Node *node, BinarySearchTree *tree) {
    __rotation_base(node, tree, 1);
}
void __rr_rotation(Node *node, BinarySearchTree *tree) {
    __rotation_base(node, tree, 0);
}
void __rotation(Node *node, int bf, BinarySearchTree *tree) {
    int first_child = (bf == -2), second_child = 0;
    Node *first_node = node->children[first_child];

    if ((first_node->children[0] == NULL) || (first_node->children[1] != NULL && \
            first_node->children[1]->height > first_node->children[0]->height))
        second_child = 1;
    if (first_child == 0 && second_child == 0) {//LL  
        __ll_rotation(node, tree);
    }
    else if (first_child == 1 && second_child == 1) //RR 
        __rr_rotation(node, tree);

    else if (first_child == 1 && second_child == 0) {//RL

        __ll_rotation(node->children[1], tree);
        __rr_rotation(node, tree);
    }
    else { //LR
        __rr_rotation(node->children[0], tree);
        __ll_rotation(node, tree);  
    } 
}

void __maintain(BinarySearchTree *self, Node *node) {

    while (node->mother != NULL) {
        node = node->mother;
        int bf = __get_bf(node);
        if (abs(bf) < 2) {
            int old_height = node->height;
            __update_height(node);
            if (old_height == node->height) break;
        }
        else 
            __rotation(node, bf, self);
    }
}


void insert(BinarySearchTree *self, int value) {
    Node *new_node = create_node(value);
    if (self->root == NULL) {
        self->root = new_node;
        return;
    }
    Node *parent = __search_parent(self, value);
    parent->children[parent->value < value] = new_node;
    new_node->mother = parent;
    __maintain(self, new_node);
}

Node* search(BinarySearchTree *self, int value) {
    if (self->root->value == value) 
        return self->root;
    Node *parent = __search_parent(self, value);
    return parent->children[parent->value < value];
}   

Node *__find_replacement_base(Node *target, char right_child) {
    Node *replacement = NULL;
    if (target->children[right_child] != NULL) {
        replacement = target->children[right_child];
        while (replacement->children[!right_child] != NULL)
            replacement = replacement->children[!right_child];
    }
    return replacement;
}

Node *__find_replacement(Node *target) {
    Node *replacement = __find_replacement_base(target, 0);
    if (replacement == NULL) __find_replacement_base(target, 1);
    return replacement;
}

void __kill_child(Node *target) {
    if (target->mother != NULL) 
        target->mother->children[target->value > target->mother->value] = NULL;
}
void delete(BinarySearchTree *self, int value) {
    Node *target = search(self, value);
    Node *replacement = __find_replacement(target);
    if (replacement != NULL) {
        int save = replacement->value;
        Node *maintain_target = replacement->mother;
        __kill_child(replacement);
        swap(replacement->value, target->value);
        __maintain(self, replacement);
        free(replacement);
    }
    else {
        target->height = 0;
        __maintain(self, target);
        __kill_child(target);
        if (self->root == target) 
            self->root = NULL;
        free(target);
    } 
}



void get_form(Node *node, int index, int *array) {
    if (node != NULL) {
        array[index] = node->value;
        get_form(node->children[0], (index << 1), array);
        get_form(node->children[1], (index << 1) + 1, array);
    }
}

void tree_show(BinarySearchTree *tree) {
    int *array = calloc(256, sizeof(int));
    get_form(tree->root, 1, array);
    int check = 2;
    for (int i = 1;i < 256;i++) {
        if (i == check) {
            printf("\n");
            check *= 2;
        }
        printf("%d ", array[i]);
    }

}


int main() {
    BinarySearchTree *tree = create_binary_search_tree();
    char op[10];
    while (1) {
        scanf("%s", op);
        int v;
        if (op[0] == 'i') {
            scanf("%d", &v);
            insert(tree, v);
        }
        else if (op[0] == 'd') {
            scanf("%d", &v);
            delete(tree, v);
        }
        else if (op[0] == 'e')
            break;
    }
    tree_show(tree);

    return 0;
}

