/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include <malloc.h>
#include <stdio.h>
#include "heap.h"

uint32_t parent(uint32_t key)
{
    return (key-1)/2;
}

uint32_t left(uint32_t key)
{
    return 2*key+1;
}

uint32_t right(uint32_t key)
{
    return 2*key+2;
}

void swap(Entry *x, Entry *y)
{
    Entry temp = *x;
    *x = *y;
    *y = temp;
}

Heap init_heap(uint32_t max_num_entries)
{
    Entry* entries = (Entry*) malloc(max_num_entries * sizeof(Entry));

    Heap h = (Heap){
            .max_num_entries=max_num_entries, .num_entries=0,
            .entries=entries};
    return h;
}

void heap_put(Heap *ms, Entry entry)
{
    if(ms->num_entries+1 >= ms->max_num_entries) {
        exit(2);
    }

    ms->num_entries++;
    uint32_t i = ms->num_entries-1;
    ms->entries[i] = entry;

    while(i != 0 && ms->entries[parent(i)].key > ms->entries[i].key)
    {
        swap(&ms->entries[i], &ms->entries[parent(i)]);
        i = parent(i);
    }
}

uint32_t heap_get(Heap *heap, uint32_t key)
{
    uint32_t index = 0;
    while(heap->entries[index].key != key)
    {
        if(heap->entries[index].key < key)
        {
            index = left(index);
        } else {
            index = right(index);
        }
        
        if(index > heap->num_entries)
        {
            return -1;
        }
    }
    return index;
}

void show_heap(Heap *heap)
{
    printf("[");
    for(uint32_t i = 0; i < heap->num_entries; ++i)
    {
        printf("(%d, %d)", heap->entries[i].key, heap->entries[i].value);
    }
    printf("]\n");
}

void free_heap(Heap *heap)
{
    free(heap->entries);
}