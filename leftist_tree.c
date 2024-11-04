#include<stdio.h>
#include<stdlib.h>

#define LEFTIST_TREE_VALUE int


typedef struct leftist_tree_node {
    LEFTIST_TREE_VALUE value;
    struct leftist_tree_node *left, *right, *parent;
}LeftistTreeNode;

LeftistTreeNode *create_leftist_tree_node(LEFTIST_TREE_VALUE value) {
    LeftistTreeNode* node = malloc(sizeof(LeftistTreeNode));
    node->value = value;
    node->left = node->right = node->parent = NULL;
    return node;
}

char l_tree_greater(LEFTIST_TREE_VALUE a, LEFTIST_TREE_VALUE b) {
    return a > b;
}

int shortest(LeftistTreeNode *a) {
    if (a == NULL) return 0;
    return 1 + (a->right != NULL && a->left != NULL);
}


LeftistTreeNode *meld(LeftistTreeNode *a, LeftistTreeNode *b) {
    LeftistTreeNode *new_root = NULL;
    LeftistTreeNode *last_terminal = NULL, **terminal_tree = &new_root;

    while (a != NULL || b != NULL) {
        LeftistTreeNode **new_terminal = &a;

        if (a == NULL || (b != NULL && l_tree_greater(a->value, b->value)))
           new_terminal = &b;

        (*new_terminal)->parent = last_terminal;
        *terminal_tree = *new_terminal;

        last_terminal = *terminal_tree;
        terminal_tree = &((*terminal_tree)->right);

        *new_terminal = (*new_terminal)->right;
        
    }

    while (last_terminal != NULL) {
        if (shortest(last_terminal->right) > shortest(last_terminal->left)) {
            LeftistTreeNode *save = last_terminal->left;
            last_terminal->left = last_terminal->right;
            last_terminal->right = save;
        }

        last_terminal = last_terminal->parent;

    }
    return new_root;

}

void insert(LeftistTreeNode **a, LEFTIST_TREE_VALUE value) {
    *a = meld(*a, create_leftist_tree_node(value));
}

void delete(LeftistTreeNode **a) {
    LeftistTreeNode *left = (*a)->left, *right = (*a)->right;
    free(*a);
    *a = meld(left, right);
}



int main() {
    LeftistTreeNode *root = create_leftist_tree_node(4);
    printf("top: %d\n", root->value);
    insert(&root, 3);
    printf("top: %d\n", root->value);
    insert(&root, 5);
    printf("top: %d\n", root->value);
    insert(&root, 0);
    printf("top: %d\n", root->value);
    insert(&root, 7);
    printf("top: %d\n", root->value);
    delete(&root);
    printf("top: %d\n", root->value);
    delete(&root);
    printf("top: %d\n", root->value);
    delete(&root);
    printf("top: %d\n", root->value);
}