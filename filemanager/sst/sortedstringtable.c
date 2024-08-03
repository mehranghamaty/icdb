//
// Created by mehran on 12/13/23.
//

#include <malloc.h>
#include "sortedstringtable.h"
#include "../../datastructures/bst/binarysearchtree.h"


SST* sst_make(char* file_name, Node* node)
{
    FILE* f = fopen(file_name, "w");
    bst_write_to_file(f, node);
    fclose(f);
    SST* sst = malloc(sizeof(SST));
    *sst = (SST){.file=f, .file_location=file_name};
    return sst;
}

void sst_free(SST* sst)
{
    free(sst->file_location);
    free(sst);
}