/**
 * This file is copyrighted by Meandering LLC 2023
 */

#ifndef FILTER_BINARYSEARCHTREE_H
#define FILTER_BINARYSEARCHTREE_H

#include <stdint.h>
#include <bits/types/FILE.h>
#include "../support/node.h"

typedef struct Tree {
    uint32_t n_lvls;
    uint32_t n_nodes;
    Node* root;
} Tree;

Tree* bst_make();

Node* bst_insert_item(Tree* bst, uint32_t key, uint32_t value);
Node* bst_insert_item_(Node* node, uint32_t key, uint32_t value, uint32_t lvl);
//int32_t bst_delete_item(Node* bst, uint32_t key);

Node* bst_find_and_remove_subtree_of_size(Tree* bst, uint32_t size);
Node* bst_find_and_remove_subtree_of_size_(Node* bst, uint32_t size);

Node* bst_get(Node* bst, uint32_t key);
//Node* bst_scan(Node* bst, uint32_t start, uint32_t end);

void bst_show(Tree* bst);
void bst_show_(Node* bst, uint32_t tab);

void bst_free(Tree* bst);
void bst_free_(Node* node);

void bst_write_to_file(FILE* fptr, Node* root);
void bst_write_to_file_(FILE* fptr, Node* root);
void bst_read_from_file(FILE* fptr, Node* to_append);

#endif //FILTER_BINARYSEARCHTREE_H
