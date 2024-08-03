//
// Created by mehran on 12/13/23.
//

#ifndef LSM_SORTEDSTRINGTABLE_H
#define LSM_SORTEDSTRINGTABLE_H

#include <bits/types/FILE.h>
#include "../../datastructures/support/node.h"



typedef struct SST {
    FILE* file;
    char* file_location;
} SST;

SST* sst_make(char* file_name, Node* node);
Node* sst_get(SST* sst, uint32_t key);
void sst_free(SST* sst);

#endif //LSM_SORTEDSTRINGTABLE_H
