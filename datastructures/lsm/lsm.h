/**
 * This file is copyrighted by Meandering LLC 2023
 */

#ifndef FILTER_LSM_H
#define FILTER_LSM_H

#include <pthread.h>

#include "../support/node.h"
#include "../bst/binarysearchtree.h"
#include "../../filemanager/level/lsm_level.h"
#include "../../parsers/config/config_parser.h"
#include "../../filemanager/wal/writeaheadlog.h"

typedef struct lsm_tree LSMTree;

LSMTree* lsm_make(ServerConfig sc);
Node* lsm_put(LSMTree* tree, uint32_t key, uint32_t value);
Node* lsm_get(LSMTree* tree, uint32_t key);
Node* lsm_delete(LSMTree* tree, uint32_t key);
Node* lsm_scan(LSMTree* tree, uint32_t start, uint32_t end);
void lsm_flush(LSMTree* tree);
void lsm_compact(LSMTree* tree);
Node* lsm_run_instruction(LSMTree* lsm, Instruction ins);
void lsm_free(LSMTree* tree);
void lsm_wal_replay(LSMTree *tree);

#endif //FILTER_LSM_H
