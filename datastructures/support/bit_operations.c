//
// Created by mehra on 12/8/2023.
//

#include <stdint.h>
#include "bit_operations.h"

int get_bit(char* bits, uint32_t element) {
    uint32_t byte_index = element/8;
    uint32_t bit_index = element % 8;
    uint32_t bit_mask = (1 << bit_index);
    return ((bits[byte_index] & bit_mask) != 0);
}
void set_bit(char* bits, uint32_t element) {
    uint32_t byte_index = element/8;
    uint32_t bit_index = element % 8;
    uint32_t bit_mask = (1 << bit_index);
    bits[byte_index] |= bit_mask;
}
void clear_bit(char* bits, uint32_t element) {
    uint32_t byte_index = element/8;
    uint32_t bit_index = element%8;
    uint32_t bit_mask = (1<< bit_index);
    bits[byte_index] &= ~bit_mask;
}