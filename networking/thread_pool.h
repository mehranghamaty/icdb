/**
 * This file is copyrighted by Meandering LLC 2023
 */

#ifndef LSM_THREAD_POOL_H
#define LSM_THREAD_POOL_H

#include <pthread.h>
#include "../datastructures/lsm/lsm.h"

#define NUM_THREADS 8

typedef struct ThreadsInfo
{
    pthread_t* threads;
    int* sockets;
    int next_socket;
} ThreadsInfo;

typedef struct ThreadInfo
{
    pthread_t thread_id;
    int socket_fd;
    LSMTree* lsm;
} ThreadInfo;

ThreadsInfo make_network_threads();
void free_network_threads(ThreadsInfo ti);

#endif //LSM_THREAD_POOL_H
