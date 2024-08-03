//
// Created by mehra on 12/9/2023.
//

#ifndef FILTER_REDBLACK_H
#define FILTER_REDBLACK_H

#include <stdint.h>
#include "../support/node.h"

struct Node* rb_make(uint32_t initial_node);
void rb_insert_item(struct Node* rb, uint32_t key, uint32_t value);
void rb_delete_item(struct Node* rb, uint32_t key);
struct Node* rb_get(struct Node* rb, uint32_t key);
struct Node* rb_scan(struct Node* rb, uint32_t start, uint32_t end);

#endif //FILTER_REDBLACK_H
