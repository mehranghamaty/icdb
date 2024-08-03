//
// Created by mehran on 12/13/23.
//

#ifndef LSM_CONFIG_PARSER_H
#define LSM_CONFIG_PARSER_H

#include <bits/types/FILE.h>

typedef struct ServerConfig {
    char* file_location;
    char* directory_location;
    char* write_ahead_log_location;
    int max_memtable_size;
    int num_levels;
} ServerConfig;

ServerConfig sc_make(char* file_location);
void sc_free(ServerConfig sc);

#endif //LSM_CONFIG_PARSER_H
