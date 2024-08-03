/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include "../datastructures/lsm/lsm.h"
#include "handler.h"

#include <stdlib.h>
#include <stdio.h>


void *request_thread(void *vargp)
{
    //printf("In thread %lu\n", pthread_self());
    ExperimentParameters *ep = (ExperimentParameters*)vargp;

    for(int i = 0; i < ep->num_requests/ep->num_threads; ++i)
    {
        int key = random() % 100;
        int val = random() % 100;
        //printf("Adding (%d, %d)\n", key, val);
        lsm_put(&ep->tree, key, val);
    }

    return NULL;
}