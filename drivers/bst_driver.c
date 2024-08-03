
/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include <stdio.h>
#include "../datastructures/bst/binarysearchtree.h"


int bst_driver() {
    Tree tree = bst_make(5, 2);
    bst_insert_item(tree.root, 3, 2);
    bst_insert_item(tree.root, 1, 2);
    bst_insert_item(tree.root, 9, 2);
    bst_insert_item(tree.root, 8, 2);

    show_bst(tree.root, 0);
    FILE* fptr = fopen("C:\\Users\\mehra\\test.txt", "w");
    bst_write_to_file(fptr, tree.root);
    fclose(fptr);
    free_bst(tree.root);
    return 0;
}
