#include<stdio.h>
#include<stdlib.h>
#define swap(a, b) {\
    int save = a;\
    a = b;\
    b = save;\
}


typedef struct min_max_heap {
    int *data;
    int new_value_pos;
}MinMaxHeap;

MinMaxHeap *create_min_max_heap() {
    MinMaxHeap *heap = malloc(sizeof(MinMaxHeap));
    heap->data = malloc(sizeof(int) * 10000);
    heap->new_value_pos = 1;
    return heap;
}

int __get_min_max_level(int pos) {
    /*
        min level == 1
        max level == 0
    */
    int min_max = 1;
    while (pos / 2 != 0) {
        pos /= 2;
        min_max ^= 1;
    }
    return min_max;
    
}

void insert(MinMaxHeap *heap, int value) {
    int pos = heap->new_value_pos;
    heap->new_value_pos++;
    heap->data[pos] = value;
    int now_pos = pos;
    int level = __get_min_max_level(pos);
    while (now_pos > 1) {
        now_pos = now_pos / 2;
        level ^= 1;
        if ((level % 2 == 1 && heap->data[now_pos] > heap->data[pos]) || \
            (level % 2 == 0 && heap->data[now_pos] < heap->data[pos])) {
            swap(heap->data[now_pos], heap->data[pos]);
            pos = now_pos;
        }
        else if (pos / 2 != now_pos)
            break;
    }
}


int __get_min_grand_child(MinMaxHeap *heap, int index) {
    int target_index = index * 4, min_index = index;
    if (target_index >= heap->new_value_pos) return index;//代表不用處理了

    for (int i = target_index;i < target_index + 4 && i < heap->new_value_pos;i++) {
        if (heap->data[min_index] > heap->data[i])
            min_index = i;
    }
    return min_index;

}

void delete_min(MinMaxHeap *heap) {
    heap->new_value_pos--;
    swap(heap->data[1], heap->data[heap->new_value_pos]);
    int now_pos = 1;
    int min_index = __get_min_grand_child(heap, now_pos);
    while (min_index != now_pos) {
        swap(heap->data[now_pos], heap->data[min_index]);
        now_pos = min_index;
        min_index = __get_min_grand_child(heap, now_pos);
    } 
}



int main() {
    MinMaxHeap *heap = create_min_max_heap();
    insert(heap, 70);
    insert(heap, 7);
    insert(heap, 40);
    insert(heap, 30);
    insert(heap, 9);
    insert(heap, 15);
    insert(heap, 5);
    insert(heap, 20);
    insert(heap, 17);
    insert(heap, 45);
    insert(heap, 132);
    insert(heap, 6);
    insert(heap, 123);
    insert(heap, 114);


    delete_min(heap);
    int meow = 2;
    for (int i = 1;i < heap->new_value_pos;i++) {
        if (i == meow) {
            printf("\n");
            meow *= 2;
        }
        printf("%d ", heap->data[i]);
    }
        
    printf("\n");

    
}