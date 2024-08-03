//
// Created by mehran on 12/13/23.
//

#include <sys/stat.h>
#include <stdlib.h>
#include <malloc.h>
#include "lsm_level.h"
#include "../../datastructures/filters/bloom_filter.h"

//todo, calculate number of SSTs
//from the max_size
//todo find some way to get bloom_filter size
LSMLevel* lsml_make(ServerConfig sc, LSMLevelConfig lsmlc)
{
    char* directory = malloc(100 * sizeof(char));

    sprintf(directory, "%s%d", sc.directory_location, lsmlc.level);

    struct stat st = {0};
    if(stat(directory, &st) == -1)
    {
        mkdir(directory, 0700);
    }
    SST* blocks = malloc(lsmlc.num_blocks * sizeof(SST));

    BloomFilter bloom_filter = init_bloom_filter(lsmlc.filter_size, lsmlc.fn_cnt);
    LSMLevel* lsm_level = malloc(sizeof(LSMLevel));//lsml_make(sc, lsmlc);
    *lsm_level = (LSMLevel){.directory=directory, .blocks=blocks,
                            .next_slot=0, .lsml_c=lsmlc,
                            .bf=bloom_filter};
    return lsm_level;
}

void lsml_add_block(LSMLevel* lsm_level, Node* sub_tree)
{
    char filename[100];
    if(sscanf(filename, "%s%d.txt", lsm_level->directory, lsm_level->next_slot) !=2)
    {
        perror("error generating block filename");
        exit(EXIT_FAILURE);
    }
    SST* sst = sst_make(filename, sub_tree);
    lsml_add_block_(lsm_level, sst);
}

void lsml_add_block_(LSMLevel* lsm_level, SST* block)
{
    //todo idk if this is right
    lsm_level->blocks[lsm_level->next_slot++] = *block;

}

void lsml_free(LSMLevel* lsm_level)
{
    free(lsm_level->directory);
    for(int i = 0; i < lsm_level->lsml_c.num_blocks; ++i)
    {
        sst_free(&lsm_level->blocks[i]);
    }
    free(lsm_level);
}