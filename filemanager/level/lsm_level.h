//
// Created by mehran on 12/13/23.
//

#ifndef LSM_LSM_LEVEL_H
#define LSM_LSM_LEVEL_H

#include "../sst/sortedstringtable.h"
#include "../../datastructures/filters/bloom_filter.h"
#include "../../parsers/config/config_parser.h"

typedef struct LSMLevelConfig
{
    int num_blocks;
    int block_size;
    int filter_size;
    int fn_cnt;
    int level;
} LSMLevelConfig;

typedef struct LSMLevel
{
    char* directory;
    SST* blocks;
    int next_slot;
    LSMLevelConfig lsml_c;
    BloomFilter bf;
} LSMLevel;

LSMLevel* lsml_make(ServerConfig sc, LSMLevelConfig lsml_config);
void lsml_add_block(LSMLevel* lsm_level, Node* sub_tree);
void lsml_add_block_(LSMLevel* lsm_level, SST* block);
Node* lsml_get(LSMLevel* lsm_level, uint32_t key);
void lsml_compact(LSMLevel* lsm_level, LSMLevel lower_level);
void lsml_free(LSMLevel* lsm_level);

#endif //LSM_LSM_LEVEL_H
