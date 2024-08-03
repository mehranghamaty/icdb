/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include "../datastructures/heap/heap.h"


int heap_main() {
    Heap heap = init_heap(5);

    show_heap(&heap);
    heap_put(&heap, (Entry){.key=2,.value=5});
    heap_put(&heap, (Entry){.key=3,.value=6});
    heap_put(&heap, (Entry){.key=1,.value=2});
    show_heap(&heap);
    free_heap(&heap);
    return 0;
}
