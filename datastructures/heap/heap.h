/**
 * This file is copyrighted by Meandering LLC 2023
 */


#ifndef FILTER_HEAP_H
#define FILTER_HEAP_H

#include <stdint.h>

typedef struct Entry {
    uint32_t key;
    uint32_t value;
} Entry;

typedef struct Heap {
    uint32_t max_num_entries;
    uint32_t num_entries;
    Entry* entries;
} Heap;

uint32_t parent(uint32_t key);

uint32_t left(uint32_t key);

uint32_t right(uint32_t key);

void swap(Entry *x, Entry *y);

Heap init_heap(uint32_t max_num_entries);
void heap_put(Heap *h, Entry entry);

void heap_delete(Heap *h, uint32_t key);
//void heap_decrease_key(Heap *h, uint32_t key, uint32_t new_value);
uint32_t heap_get(Heap *h, uint32_t key);
//void heap_scan(Heap *h, uint32_t key_start, uint32_t key_end);
void show_heap(Heap *h);
void free_heap(Heap *h);

#endif //FILTER_HEAP_H
