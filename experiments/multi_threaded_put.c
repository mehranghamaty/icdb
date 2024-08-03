/**
 * This file is copyrighted by Meandering LLC 2023
 *
 * Why am I even trying this it's probably worse because I lock the whole tree everytime
 */

#include "../datastructures/lsm/lsm.h"
#include "handler.h"
#include <time.h>
#include <stdio.h>

#define MAX_THREADS 8
#define NUM_REQUESTS 10000

int run_experiment(int num_threads)
{
    LSMTree lsm = lsm_make();

    ExperimentParameters ep = (ExperimentParameters) {.num_requests=NUM_REQUESTS, .num_threads=num_threads, .tree=lsm};

    pthread_t threads[num_threads];
    clock_t start = clock();

    for (int i = 0; i < ep.num_threads; ++i) {
        pthread_create(&threads[i], NULL, (void *) &request_thread, (void *) &ep);
        //printf("Launched thread %lu.\n", threads[i]);
    }

    for (int i = 0; i < ep.num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    clock_t duration = clock() - start;

    lsm_free(lsm);
    return duration;
}

int main()
{
    clock_t results[MAX_THREADS];
    for(int num_threads = 1; num_threads <= MAX_THREADS; ++num_threads)
    {
        results[num_threads-1] = run_experiment(num_threads);
    }

    for(int i = 0; i < MAX_THREADS; ++i)
    {
        printf("(%d, %ld)", i+1, results[i]);
    }
    //printf("Took %ld seconds", duration);
    return 1;
}