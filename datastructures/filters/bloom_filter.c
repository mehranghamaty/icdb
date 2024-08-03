//
// Created by mehra on 12/8/2023.
//

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "bloom_filter.h"
#include "../support/hash_functions.h"
#include "../support/bit_operations.h"

BloomFilter init_bloom_filter(uint32_t filter_size, uint32_t fn_cnt)
{
    Hash* hash_fns = malloc(fn_cnt * sizeof(Hash));

    FnParams* fn_params = malloc(fn_cnt * sizeof(FnParams));

    uint32_t num_bits = (filter_size/8)+1;
    char* bits = malloc(num_bits);

    BloomFilter bf = (BloomFilter){
        .filter_size=filter_size, .fn_cnt=fn_cnt, .hash_fns=hash_fns,
        .fn_params=fn_params, .bits=bits};

    for(uint32_t i = 0; i < num_bits; ++i)
    {
        bits[i] = 0;
    }
    for(uint32_t i = 0; i < fn_cnt; ++i)
    {
        bf.hash_fns[i] = &murmur3_32;
    }
    for(uint32_t i = 0; i < fn_cnt; ++i)
    {
        bf.fn_params[i] = (FnParams){.len=filter_size, .seed=rand()*100};
    }

    return bf;
}

void insert_element(BloomFilter* bf, const uint8_t* x)
{
    for(uint32_t i = 0; i < bf->fn_cnt; ++i)
    {
        uint32_t hashed = bf->hash_fns[i](x, bf->fn_params[i].len, bf->fn_params[i].seed);
        uint32_t index = hashed % bf->filter_size;
        set_bit(bf->bits, index);
    }
}

uint8_t exists_in(BloomFilter* bf, const uint8_t* x)
{
    for(uint32_t i = 0; i < bf->fn_cnt; ++i)
    {
        uint32_t hashed = bf->hash_fns[i](x, bf->fn_params[i].len, bf->fn_params[i].seed);
        uint32_t index = hashed % bf->filter_size;
        if(!get_bit(bf->bits, index)) return 0;
    }
    return 1;
}

void show_filter(BloomFilter* bf) {
    char buffer[bf->filter_size+1];
    printf("showing datastructures\n");

    for(uint32_t i = 0; i < bf->filter_size; ++i) {
        buffer[i] = '0'+get_bit(bf->bits, i);
    }
    buffer[bf->filter_size] = '\n';

    printf(buffer);
    fflush(stdout);

}

void free_filter(BloomFilter *bf) {
    free(bf->hash_fns);
    free(bf->bits);
}

