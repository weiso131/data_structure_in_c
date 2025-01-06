#include<stdio.h>
#include<stdlib.h>

#define swap(a, b) {\
    int save = a;\
    a = b;\
    b = save;\
}

typedef struct deap{
    int next_point;
    int *data;
}Deap;

Deap *create_deap() {
    Deap *deap = malloc(sizeof(Deap));
    deap->next_point = 2;
    deap->data = malloc(sizeof(int) * 1000);
    return deap;
}

int __level_count(int index) {
    int i = 0;
    while (1 << (i + 1) <= index)
        i++;
    return 1 << i;
}

int __get_link_target(int index, int deap_count, int level) {
    int link_target;
    if (index - level / 2 >= level) { //max heap的半邊
        link_target = index - level / 2;
        if (link_target * 2 < deap_count)
            return link_target * 2;
    }
    else {
        link_target = index + level / 2;
        if (link_target >= deap_count) 
            return link_target / 2;
    }
    return link_target;
}

void __go_up(Deap *deap, int index) {
    int level = __level_count(index);
    char at_max_heap = index - level / 2 >= level;
    while (!((at_max_heap) ^ (deap->data[index] > deap->data[index / 2])) && index > 3) {
        swap(deap->data[index], deap->data[index / 2]);
        index /= 2;
    }
}

void __maintain(Deap *deap, int index, int link_target) {
    int level = __level_count(index);
    char at_max_heap = index - level / 2 >= level;
    if (index > 3 && !((at_max_heap) ^ (deap->data[index] > deap->data[index / 2]))) {
        swap(deap->data[index], deap->data[index / 2]);
        index = index / 2;
    }
    else if (!at_max_heap && deap->data[index] > deap->data[link_target]) {
        swap(deap->data[index], deap->data[link_target]);
        index = link_target;
    }
    else if (at_max_heap && deap->data[index] < deap->data[link_target]) {
        if (link_target + 1 < deap->next_point && link_target > index) { //連到兩個點
            if (deap->data[link_target] < deap->data[link_target + 1])
                link_target++;
        }
        swap(deap->data[index], deap->data[link_target]);
        index = link_target;
    }
    __go_up(deap, index);
}


void insert(Deap *deap, int value) {
    int index = deap->next_point;
    int level = __level_count(index);
    deap->data[index] = value;
    deap->next_point++;

    int link_target = __get_link_target(index, deap->next_point, level);
    if (index == 2) return;

    __maintain(deap, index, link_target);
}

void delete_min(Deap *deap) {
    int index = 2;
    while (index * 2 < deap->next_point) {
        int swap_index = index * 2;
        if (index * 2 + 1 < deap->next_point && deap->data[swap_index] > deap->data[swap_index + 1])
            swap_index++;
        swap(deap->data[index], deap->data[swap_index]);
        index = swap_index;
    }

    deap->next_point--;
    swap(deap->data[index], deap->data[deap->next_point]);

    if (index == deap->next_point) return;
    int level = __level_count(index);
    int link_target = __get_link_target(index, deap->next_point, level);
    __maintain(deap, index, link_target);
}


void show(Deap *deap) {
    int check = 4;
    for (int i = 2;i < deap->next_point;i++) {
        if (i == check) {
            check *= 2;
            printf("\n");
        }
        printf("%d ", deap->data[i]);
    }
    printf("\n\n");
}



int main () {
    Deap *deap = create_deap();
    insert(deap, 8);
    insert(deap, 45);
    insert(deap, 9);
    insert(deap, 19);
    insert(deap, 20);
    insert(deap, 5);
    insert(deap, 15);

    insert(deap, 25);
    insert(deap, 40);
    insert(deap, 30);
    insert(deap, 10);

    delete_min(deap);
    show(deap);
    

}