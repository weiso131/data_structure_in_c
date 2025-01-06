#include<stdio.h>
#include<stdlib.h>

#define swap(a, b) {\
    int save = a;\
    a = b;\
    b = save;\
}

typedef struct smmp {
    int next_point;
    int *data;
}Smmp;

Smmp *create_smmp() {
    Smmp *smmp = malloc(sizeof(Smmp));
    smmp->next_point = 2;
    smmp->data = malloc(sizeof(int) * 1000);
    return smmp;
}

void __go_up(Smmp *smmp, int index) {
    int right_parent = index / 2;
    if (right_parent == 1) return;
    if (right_parent % 2 == 0) right_parent++;

    if (smmp->data[right_parent] < smmp->data[index]) {
        swap(smmp->data[right_parent], smmp->data[index]);
        __go_up(smmp, right_parent);
    }
    else if (smmp->data[right_parent - 1] > smmp->data[index]) {
        swap(smmp->data[right_parent - 1], smmp->data[index]);
        __go_up(smmp, right_parent - 1);
    }

}

void insert(Smmp *smmp, int value) {
    int index = smmp->next_point;
    smmp->data[index] = value;
    smmp->next_point++;

    if (index % 2 && smmp->data[index] < smmp->data[index - 1]) {
        swap(smmp->data[index], smmp->data[index - 1]);
        index--;
    }
    __go_up(smmp, index);
}

int __min_go_down(Smmp *smmp, int index) {
    int self_child = index * 2;
    int brother_child = (index + 1) * 2;

    if (brother_child >= smmp->next_point && self_child >= smmp->next_point)
        return index;
    else if (brother_child >= smmp->next_point) {
        if (smmp->data[self_child] < smmp->data[index]) {
            swap(smmp->data[self_child], smmp->data[index]);
            index = self_child;
        }
        return index;
    }
    else if (self_child >= smmp->next_point) {
        if (smmp->data[brother_child] < smmp->data[index]) {
            swap(smmp->data[brother_child], smmp->data[index]);
            index = brother_child;
        }
        return index;
    }
    else {
        int swap_target = self_child;
        if (smmp->data[brother_child] < smmp->data[self_child])
            swap_target = brother_child;
        if (smmp->data[swap_target] < smmp->data[index]) {
            swap(smmp->data[swap_target], smmp->data[index]);
            index = swap_target;
        }
        return __min_go_down(smmp, index);
    }

    



}

void delete_min(Smmp *smmp) {
    int index = 2;
    smmp->next_point--;
    swap(smmp->data[index], smmp->data[smmp->next_point]);

    index = __min_go_down(smmp, index);
    __go_up(smmp, index);

}


void show(Smmp *smmp) {
    int check = 4;
    for (int i = 2;i < smmp->next_point;i++) {
        if (i == check) {
            check *= 2;
            printf("\n");
        }
        printf("%d ", smmp->data[i]);
    }
    printf("\n\n");
}


int main() {
    Smmp *smmp = create_smmp();
    insert(smmp, 2);
    insert(smmp, 80);
    insert(smmp, 60);
    insert(smmp, 8);
    insert(smmp, 40);
    insert(smmp, 4);
    insert(smmp, 12);
    insert(smmp, 20);
    insert(smmp, 10);
    insert(smmp, 16);
    insert(smmp, 14);
    insert(smmp, 30);
    insert(smmp, 6);
    insert(smmp, 100);
    delete_min(smmp);
    show(smmp);

}