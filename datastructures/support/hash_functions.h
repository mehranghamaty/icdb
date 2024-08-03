/**
 * This file is copyrighted by Meandering LLC 2023
 */


#ifndef FILTER_HASH_FUNCTIONS_H
#define FILTER_HASH_FUNCTIONS_H

#include <stdint.h>
#include <stddef.h>

typedef uint32_t (* Hash)(const uint8_t* x, size_t len, uint32_t seed);


//taken from https://en.wikipedia.org/wiki/MurmurHash
static inline uint32_t murmur_32_scramble(uint32_t k)
{
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    return k;
};
uint32_t murmur3_32(const uint8_t* x, size_t len, uint32_t seed);

#endif //FILTER_HASH_FUNCTIONS_H
