//
// Created by mehran on 12/13/23.
//

#ifndef LSM_WRITEAHEADLOG_H
#define LSM_WRITEAHEADLOG_H

#include "../../parsers/network_requests/parser.h"
#include "../../datastructures/lsm/lsm.h"

#include <pthread.h>
#include <bits/types/FILE.h>

typedef struct WriteAheadLog {
    char* file_location;
    FILE* file;
    pthread_mutex_t lock;
} WriteAheadLog;

WriteAheadLog* wal_make(char* file_location);
void wal_write_cmd(WriteAheadLog* wal, Instruction ins);
void wal_clear(WriteAheadLog* wal);
void wal_free(WriteAheadLog* wal);

#endif //LSM_WRITEAHEADLOG_H
