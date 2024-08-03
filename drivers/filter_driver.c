/**
 * This file is copyrighted by Meandering LLC 2023
 */
#include <stdio.h>
#include <malloc.h>
#include "../datastructures/filters/bloom_filter.h"


int filter_driver() {

    BloomFilter bf = init_bloom_filter(12, 3);

    uint8_t key[5] = {1,2,3,4,5};


    insert_element(&bf, key);
    show_filter(&bf);

    uint8_t exists = exists_in(&bf, key);

    char buffer[2] = {'0'+exists, '\n'};
    printf(buffer);
    fflush(stdout);


    free_filter(&bf);
    return 0;
}
