/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include <stdio.h>
#include <malloc.h>
#include "binarysearchtree.h"

Tree* bst_make()
{
    Tree* tree = malloc(sizeof(Tree));
    *tree = (Tree){.n_lvls=0, .n_nodes=0, .root=NULL};
    return tree;
}

Node* bst_insert_item(Tree* bst, uint32_t key, uint32_t value)
{
    bst->n_nodes++;
    if(bst->root == NULL) {
        Node* root = malloc(sizeof(Node));
        *root = (Node){.key=key, .value=value, .n_children=0};
        bst->root = root;
        return root;
    }
    return bst_insert_item_(bst->root, key, value, 0);
}


Node* bst_insert_item_(Node* node, uint32_t key, uint32_t value, uint32_t lvl)
{
    if(node == NULL) {
        return NULL;
    }
    node->n_children++;

    if(node->key == key)
    {
        if(node->right == NULL)
        {
            Node* new_node = malloc(sizeof(Node));
            *new_node = (Node){.key=key, .value=value, .n_children=0, .parent=node};
            node->right = new_node;
            return new_node;
        }
        if(node->left == NULL)
        {
            Node* new_node = malloc(sizeof(Node));
            *new_node = (Node){.key=key, .value=value, .n_children=0, .parent=node};
            node->left = new_node;
            return new_node;
        }

        Node* new_node = malloc(sizeof(Node));
        *new_node = (Node){.key=key, .value=value, .right=node->right, .n_children=0, .parent=node};
        node->right = new_node;
    }

    if(node->key < key)
    {
        if(node->left == NULL)
        {
            Node* new_node = malloc(sizeof(Node));
            *new_node = (Node){.key=key, .value=value, .n_children=0, .parent=node};
            node->left = new_node;
            return new_node;
        } else {
            return bst_insert_item_(node->left, key, value, lvl+1);
        }
    } else {
        if(node->right == NULL)
        {
            Node* new_node = malloc(sizeof(Node));
            *new_node = (Node){.key=key, .value=value, .n_children=0, .parent=node};
            node->right = new_node;
            return new_node;
        } else {
            return bst_insert_item_(node->right, key, value, lvl+1);
        }
    }
}

uint32_t bst_delete_item(Node *bst, uint32_t key)
{

}

Node* bst_find_and_remove_subtree_of_size(Tree* bst, uint32_t size)
{
    if(bst->root->n_children < size)
    {
        Node* tmp = bst->root;
        bst->root = NULL;
        return tmp;
    }

    Node* subtree = bst_find_and_remove_subtree_of_size_(bst->root, size);
    bst->n_nodes -= subtree->n_children;
}

Node* bst_find_and_remove_subtree_of_size_(Node* node, uint32_t size)
{
    if(node == NULL)
    {
        return NULL;
    }

    Node* ret;

    if(node->right != NULL)
    {
        if(node->right->n_children >= size
           && node->right->left->n_children < size
           && node->right->right->n_children < size)
        {
            Node* tmp = node->right;
            node->right = NULL;
            return tmp;
        }
        ret = bst_find_and_remove_subtree_of_size_(node->right, size);
        if(ret != NULL)
            return ret;
    }

    if(node->left != NULL)
    {
        if(node->left->n_children >= size
           && node->left->left->n_children < size
           && node->left->right->n_children < size)
        {
            Node* tmp = node->left;
            node->left = NULL;
            return tmp;
        }
        ret = bst_find_and_remove_subtree_of_size_(node->right, size);
        if(ret != NULL)
            return ret;
    }

    return NULL;
}


Node* bst_get(Node *bst, uint32_t key)
{
    if(bst == NULL)
    {
        return bst;
    }

    if(bst->key == key)
    {
        return bst;
    }
    if(bst->key < key)
    {
        return bst_get(bst->left, key);
    } else {
        return bst_get(bst->right, key);
    }
}

void bst_show(Tree* bst)
{
    bst_show_(bst->root, 0);
}

void bst_show_(Node* node, uint32_t tab)
{
    if(node == NULL)
        return;

    printf("(%d, %d)\t", node->key, node->value);
    bst_show_(node->right, tab);

    printf("\n");
    bst_show_(node->left, tab);
}

void bst_free(Tree* tree)
{
    bst_free_(tree->root);
    free(tree);
}

void bst_free_(Node* node)
{
    if(node == NULL)
        return;

    if(node->right != NULL)
    {
        if(node->right->right == NULL && node->right->left == NULL)
        {
            free(node->right);
        } else {
            bst_free_(node->right);
            free(node->right);
        }
    }

    if(node->left != NULL)
    {
        if(node->left->right == NULL && node->left->left == NULL)
        {
            free(node->left);
        } else {
            bst_free_(node->left);
            free(node->left);
        }
    }
}

void bst_write_to_file(FILE* fptr, Node* root)
{
    if(root == NULL)
        return;
    bst_write_to_file_(fptr, root);
    fprintf(fptr, "*");
}

void bst_write_to_file_(FILE* fptr, Node* root)
{
    if(root == NULL)
        return;
    fprintf(fptr, "%d,%d|", root->key, root->value);
    bst_write_to_file_(fptr, root->left);
    bst_write_to_file_(fptr, root->right);
}

#define BUFFERSIZE 100
void bst_read_from_file(FILE* fptr, Node* to_append)
{
    char buffer[BUFFERSIZE];

    while(fgets(buffer, BUFFERSIZE, fptr))
    {
        for(uint32_t i = 0; i < BUFFERSIZE; ++i)
        {

        }
    }
}