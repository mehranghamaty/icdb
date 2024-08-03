/**
 * This file is copyrighted by Meandering LLC 2023
 */


#include <stdio.h> //for perror
#include <stdlib.h> //for exit
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "../bst/binarysearchtree.h"
#include "../../filemanager/wal/writeaheadlog.h"
#include "lsm.h"

struct lsm_tree {
    Tree* memtable;
    LSMLevel** levels;
    WriteAheadLog* wal;
    ServerConfig sc;
    pthread_mutex_t lock;
};

LSMTree* lsm_make(ServerConfig sc)
{
    Tree* tree = bst_make();
    struct stat st = {0};
    pthread_mutex_t lock;
    if(pthread_mutex_init(&lock, NULL) != 0)
    {
        perror("failed to init lock");
        exit(EXIT_FAILURE);
    }

    if(stat(sc.directory_location, &st) == -1)
    {
        mkdir(sc.directory_location, 0700);
    }

    LSMLevel** levels = malloc(sc.num_levels * sizeof(LSMLevel*));
    for(int i = 0; i < sc.num_levels; ++i)
    {
        LSMLevelConfig  lsml_config = (LSMLevelConfig){.num_blocks=100,
                                                       .block_size=10,
                                                       .filter_size=100,
                                                       .fn_cnt=10, .level=i};

        levels[i] = lsml_make(sc, lsml_config);
    }
    WriteAheadLog* wal = wal_make(sc.write_ahead_log_location);
    LSMTree* lsm_tree = malloc(sizeof(LSMTree));
    *lsm_tree = (LSMTree){.memtable=tree, .lock=lock, .sc=sc, .wal=wal, .levels=levels};

    lsm_wal_replay(lsm_tree);
    return lsm_tree;
}

Node* lsm_put(LSMTree* tree, uint32_t key, uint32_t value)
{
    Node* node;
    pthread_mutex_lock(&tree->lock);
    if(tree->memtable->n_nodes >= tree->sc.max_memtable_size)
    {

        Node* sub_tree = bst_find_and_remove_subtree_of_size(tree->memtable,
                                            tree->levels[0]->lsml_c.block_size);

        lsml_add_block(&tree->levels[0], sub_tree);
        //flush portion of out table to disk
    }
    node = bst_insert_item(tree->memtable, key, value);
    pthread_mutex_unlock(&tree->lock);
    return node;
}

Node* lsm_get(LSMTree* tree, uint32_t key)
{
    return NULL;
}

Node* lsm_delete(LSMTree* tree, uint32_t key)
{
    return NULL;
}

Node* lsm_scan(LSMTree* tree, uint32_t start, uint32_t end)
{
    return NULL;
}

void lsm_flush(LSMTree* tree)
{
    while (tree->memtable != NULL)
    {
        Node *sub_tree = bst_find_and_remove_subtree_of_size(tree->memtable,
                                                             tree->levels[0]->lsml_c.block_size);

        lsml_add_block(&tree->levels[0], sub_tree);
        //TODO if we run out space on the next level
    }
    wal_clear(tree->wal);
}

Node* lsm_run_instruction(LSMTree* tree, Instruction ins)
{
    wal_write_cmd(tree->wal, ins);
    if (ins.cmd == PUT) {
        return lsm_put(tree, ins.arg1, ins.arg2);
    } else if (ins.cmd == GET) {
        return lsm_get(tree, ins.arg1);
    } else if (ins.cmd == DELETE) {
        return lsm_delete(tree, ins.arg1);
    } else if (ins.cmd == SCAN) {
        return lsm_scan(tree, ins.arg1, ins.arg2);
    } else if (ins.cmd == FLUSH) {
        lsm_flush(tree);
        return NULL;
    } else if (ins.cmd == COMPACT) {
        lsm_compact(tree);
        return NULL;
    } else if (ins.cmd == ERROR) {
        return NULL;
    }
}

void lsm_compact(LSMTree* tree)
{

}

void lsm_free(LSMTree* tree)
{
    lsm_flush(tree);
    bst_free(tree->memtable);
    wal_free(tree->wal);

    if(pthread_mutex_destroy(&tree->lock) != 0)
    {
        perror("failed to destroy mutex");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < tree->sc.num_levels; ++i)
    {
        lsml_free(tree->levels[i]);
    }
    free(tree->levels);
    free(tree);
}


/*
 * Not multithread safe, assuming only ran during startup.
 */
void lsm_wal_replay(LSMTree* lsm)
{

    FILE* f = fopen(lsm->wal->file_location, "r");
    if(f == NULL)
    {
        perror("Unable to open file for wal replay. Assuming no wal file exists.");
        return;
        //exit(EXIT_FAILURE);
    }

    size_t len = 30;
    char line[len];
    while(fgets(line, len, f) != EOF)
    {
        Instruction in = parse_message(line);
        lsm_run_instruction(lsm, in);
    }

    f = freopen(lsm->wal->file_location, "w", f);
    if(f == NULL)
    {
        perror("Unable to clear the wal replay file.");
        exit(EXIT_FAILURE);
    }
    if(fclose(f) != 0)
    {
        perror("Unable to close wal replay fd");
        exit(EXIT_FAILURE);
    }
}

