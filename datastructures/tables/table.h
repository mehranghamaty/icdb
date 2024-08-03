/**
 * This file is copyrighted by Meandering LLC 2023
 */

#ifndef LSM_TABLE_H
#define LSM_TABLE_H

#include "../lsm/lsm.h"

typedef struct Table {
    LSMTree* column;
    char** column_names;
    char* table_name;
    char* table_config;
} Table;

Table* table_make(char* table_config);
void table_run_command()

#endif //LSM_TABLE_H
