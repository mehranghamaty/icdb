//
// Created by mehra on 12/8/2023.
//

#ifndef FILTER_BIT_OPERATIONS_H
#define FILTER_BIT_OPERATIONS_H

#include <stdint.h>   // for uint32_t
#include <limits.h>   // for CHAR_BIT

int get_bit(char* bits, uint32_t element);
void set_bit(char* bits, uint32_t element);
void clear_bit(char* bits, uint32_t element);

static inline uint32_t rotl32 (uint32_t n, unsigned int c)
{
    const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);  // assumes width is a power of 2.

    // assert ( (c<=mask) &&"rotate by type width or more");
    c &= mask;
    return (n<<c) | (n>>( (-c)&mask ));
}

static inline uint32_t rotr32 (uint32_t n, unsigned int c)
{
    const unsigned int mask = (CHAR_BIT*sizeof(n) - 1);

    // assert ( (c<=mask) &&"rotate by type width or more");
    c &= mask;
    return (n>>c) | (n<<( (-c)&mask ));
}

#endif //FILTER_BIT_OPERATIONS_H
