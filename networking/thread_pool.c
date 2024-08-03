/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include <malloc.h>
#include <unistd.h> // for close
#include <pthread.h>
#include "thread_pool.h"


ThreadsInfo make_network_threads()
{
    pthread_t* threads = malloc(NUM_THREADS * sizeof(pthread_t));
    int* sockets = malloc(NUM_THREADS * sizeof(sockets));
    ThreadsInfo ti = (ThreadsInfo){.threads=threads, .sockets=sockets, .next_socket=0};
    return ti;
}

void free_network_threads(ThreadsInfo ti)
{
    for(int i = 0; i <NUM_THREADS; ++i)
    {
        pthread_join(ti.threads[i], NULL);
        close(ti.sockets[i]);
    }
    free(ti.sockets);
    free(ti.threads);
}