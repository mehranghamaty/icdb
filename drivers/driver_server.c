/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h> // for close
#include <pthread.h>

#include <signal.h>

#include "../networking/thread_pool.h"
#include "../networking/networking.h"
#include "../networking/handler.h"
#include "../parsers/config/config_parser.h"
#include "../datastructures/lsm/lsm.h"
#include "../filemanager/level/lsm_level.h"

static volatile int running = 1;

void intHandler(int signal) {
    printf("Got signal %d", signal);
    running = 0;
}

int main(int argc, char const* argv[]) {
    signal(SIGINT, intHandler);
    signal(SIGKILL, intHandler);
    signal(SIGTERM, intHandler);

    char* config_file = "/home/mehran/workspace/icdb/config";
    printf("Parsing config from %s\n", config_file);
    ServerConfig sc = sc_make(config_file);

    printf("Defining network threads");
    ThreadsInfo ti = make_network_threads();
    printf("Opening server to requests");
    ServerSocket ss = start_server_socket();
    LSMTree* lsm = lsm_make(sc);

    printf("Waiting on incoming connections.\n");
    fflush(stdout);
    while (running)
    {
        int new_socket;
        if ((new_socket
                     = accept(ss.server_fd, (struct sockaddr *) &ss.address,
                              &ss.address_len))
            < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Connection Accepted.");

        ThreadInfo thread_info = (ThreadInfo){.socket_fd=new_socket, .lsm=lsm};
        pthread_create(&thread_info.thread_id, NULL, server_thread, (void*)&thread_info);
        ti.sockets[ti.next_socket] = new_socket;
    }

    //joins the threads, closes the sockets, and frees memory
    free_network_threads(ti);

    // closing the listening socket
    close(ss.server_fd);
    lsm_free(lsm);
    sc_free(sc);
    return 0;
}