/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include <stdio.h>
#include <unistd.h> // for read
#include <string.h>
#include <arpa/inet.h> //for send

#include "handler.h"
#include "thread_pool.h"
#include "../datastructures/lsm/lsm.h"
#include "../parsers/network_requests/parser.h"

void *server_thread(void *vargp) {
    ThreadInfo *thread_info = (ThreadInfo *) vargp;

    //ssize_t amnt_read;
    char read_buffer[1024] = {0};

    char write_buffer[1024];
    sprintf(write_buffer, "Hello from thread %d.\n", thread_info->thread_id);
    send(thread_info->socket_fd, write_buffer, strlen(write_buffer), 0);

    Instruction  parsed;
    do {
        read(thread_info->socket_fd, read_buffer,
                         1024 - 1); // subtract 1 for the null

        printf("Message from client: %s\n", read_buffer);
        parsed = parse_message(read_buffer);
        Node* n = lsm_run_instruction(thread_info->lsm, parsed);

        if (parsed.cmd == PUT) {
            sprintf(write_buffer, "Placed item in tree.");
            send(thread_info->socket_fd, write_buffer, strlen(write_buffer), 0);
        } else if (parsed.cmd == GET) {
            sprintf(write_buffer, "Not yet implemented.");
            send(thread_info->socket_fd, write_buffer, strlen(write_buffer), 0);
        } else if (parsed.cmd == DELETE) {
            sprintf(write_buffer, "Not yet implemented.");
            send(thread_info->socket_fd, write_buffer, strlen(write_buffer), 0);
        } else if (parsed.cmd == SCAN) {
            sprintf(write_buffer, "Not yet implemented.");
            send(thread_info->socket_fd, write_buffer, strlen(write_buffer), 0);
        } else if (parsed.cmd == FLUSH) {
            sprintf(write_buffer, "Not yet implemented.");
            send(thread_info->socket_fd, write_buffer, strlen(write_buffer), 0);
        } else if (parsed.cmd == COMPACT) {
            sprintf(write_buffer, "Not yet implemented.");
            send(thread_info->socket_fd, write_buffer, strlen(write_buffer), 0);
        } else if (parsed.cmd == ERROR) {
            sprintf(write_buffer, "Could not parse the request.");
            send(thread_info->socket_fd, write_buffer, strlen(write_buffer), 0);
        }
    } while(parsed.cmd != EXIT);

    printf("Thank you for connecting\n");
    return NULL;
}

