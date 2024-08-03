/**
 * This file is copyrighted by Meandering LLC 2023
 */

#ifndef FILTER_NODE_H
#define FILTER_NODE_H

#include <stdint.h>

typedef struct Node_t Node;
struct Node_t {
    uint32_t key;
    uint32_t value;
    uint32_t n_children;
    Node* parent;
    Node* left;
    Node* right;
};


#endif //FILTER_NODE_H
