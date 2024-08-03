//
// Created by mehran on 12/8/2023.
//

#ifndef FILTER_BLOOM_FILTER_H
#define FILTER_BLOOM_FILTER_H

#include "../support/hash_functions.h"

typedef struct FnParams {
    size_t len;
    uint32_t seed;
} FnParams;

typedef struct BloomFilter {
    uint32_t filter_size;
    uint32_t fn_cnt;
    Hash* hash_fns;
    FnParams* fn_params;
    char* bits;
} BloomFilter;

typedef struct FnBank {
    uint32_t filter_size;
    uint32_t fn_cnt;
    Hash* hash_fn;
    FnParams* fn_params;
} FnBank;

BloomFilter init_bloom_filter(uint32_t filter_size, uint32_t fn_cnt);

void insert_element(BloomFilter *bf, const uint8_t* x);
uint8_t exists_in(BloomFilter *bf,const uint8_t* x);
void show_filter(BloomFilter *bf);
void free_filter(BloomFilter *bf);

#endif //FILTER_BLOOM_FILTER_H
