//
// Created by mehra on 12/8/2023.
//

#include <memory.h>
#include "hash_functions.h"
#include "bit_operations.h"


uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed)
{
    uint32_t h = seed;
    uint32_t k;
    /* Read in groups of 4. */
    for (size_t i = len >> 2; i; i--) {
        // Here is a source of differing results across endiannesses.
        // A swap here has no effects on hash properties though.
        memcpy(&k, key, sizeof(uint32_t));
        key += sizeof(uint32_t);
        h ^= murmur_32_scramble(k);
        h = (h << 13) | (h >> 19);
        h = h * 5 + 0xe6546b64;
    }
    /* Read the rest. */
    k = 0;
    for (size_t i = len & 3; i; i--) {
        k <<= 8;
        k |= key[i - 1];
    }
    // A swap is *not* necessary here because the preceding loop already
    // places the low bytes in the low places according to whatever endianness
    // we use. Swaps only apply when the memory is copied in a chunk.
    h ^= murmur_32_scramble(k);
    /* Finalize. */
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}
/*
uint32_t murmur3_32(uint32_t x, size_t len, uint32_t seed)
{
    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;

    uint32_t r1 = 15;
    uint32_t r2 = 13;

    uint32_t m = 5;
    uint32_t n = 0xe6546b64;
    uint32_t hash = seed;

    //for each fourbyte chunk of x
    uint32_t k = x;
    k = k*c1;
    k = rotl32(k, r1);
    k = k * c2;

    hash = hash XOR k;
    hash = rotl32(hash, r2);
    hash = (hash * m) + n;

    //we get to skip a lot of work
    //bc only 32 bit key

    hash = hash XOR len;
    hash = hash XOR (hash >> 16);
    hash = hash * 0x85ebca6b;
    hash = hash XOR (hash >> 13);
    hash = hash * 0xc2b2ae35;
    hash = hash XOR (hash >> 16);
}
 */