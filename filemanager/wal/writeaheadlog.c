/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include "writeaheadlog.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

WriteAheadLog* wal_make(char* file_location)
{
    pthread_mutex_t lock;
    if(pthread_mutex_init(&lock, NULL) != 0)
    {
        perror("Unable to initialize lock.");
        exit(EXIT_FAILURE);
    }
    WriteAheadLog *wal = malloc(sizeof(WriteAheadLog));
    *wal = (WriteAheadLog){.file_location=file_location, .lock=lock};
    return wal;
}

void wal_write_cmd(WriteAheadLog* wal, Instruction ins)
{
    pthread_mutex_lock(&wal->lock);
    FILE* f = fopen(wal->file_location, "a");
    if(f == NULL)
    {
        perror("Unable to open file.");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "%s %d %d", ins.cmd, ins.arg1, ins.arg2);

    if(fclose(f) != 0)
    {
        perror("Unable to close WAL fd");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_unlock(&wal->lock);
}

void wal_clear(WriteAheadLog* wal)
{
    FILE* f = fopen(wal->file_location, "r");
    if(f == NULL)
    {
        perror("Unable to open file.");
        exit(EXIT_FAILURE);
    }
    if(fclose(f) != 0)
    {
        perror("Unable to close WAL fd");
        exit(EXIT_FAILURE);
    }
}

void wal_free(WriteAheadLog* wal)
{
    if(pthread_mutex_destroy(&wal->lock) != 0)
    {
        perror("Unable to destroy WAL mutex");
        exit(EXIT_FAILURE);
    }
    free(wal);
}