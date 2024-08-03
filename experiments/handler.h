//
// Created by mehran on 12/12/23.
//

#ifndef ICDB_HANDLER_H
#define ICDB_HANDLER_H


typedef struct ExperimentParameters
{
    int num_threads;
    int num_requests;
    LSMTree tree;
} ExperimentParameters;

void *request_thread(void *vargp);

#endif //ICDB_HANDLER_H
