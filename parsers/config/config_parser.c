/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include "config_parser.h"


ServerConfig sc_make(char* file_location)
{
    size_t len = 30;
    char line[len];
    int max_size;
    int num_layers;
    FILE* f = fopen(file_location, "r");
    if(f == NULL)
    {
        perror("Error opening server config file.");
        exit(EXIT_FAILURE);
    }

    fgets(line, len, f);
    if(sscanf(line, "%d %d", &max_size, &num_layers) != 2)
    {
        perror("Error parsing config");
        exit(EXIT_FAILURE);
    }

    char* directory_location = malloc(len * sizeof(char));
    fgets(line, len, f);
    if(sscanf(line, "%s", directory_location) != 1)
    {
        perror("Error parsing config");
        exit(EXIT_FAILURE);
    }

    char* write_log_location = malloc(len*sizeof(char));
    fgets(line, len, f);
    if(sscanf(line, "%s", write_log_location) != 1)
    {
        perror("Error parsing config");
        exit(EXIT_FAILURE);
    }

    ServerConfig sc = (ServerConfig){.file_location=file_location,
                                     .max_memtable_size=max_size,
                                     .directory_location=directory_location,
                                     .write_ahead_log_location=write_log_location,
                                     .num_levels=num_layers};

    if(fclose(f) != 0)
    {
        perror("Error opening server config file.");
        exit(EXIT_FAILURE);
    }
    return sc;
}

void sc_free(ServerConfig sc)
{
    free(sc.directory_location);
}