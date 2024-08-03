/**
 * This file is copyrighted by Meandering LLC 2023
 */
 
#ifndef DRIVER_NETWORKING_H
#define DRIVER_NETWORKING_H

#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080

typedef struct ServerSocket
{
    int server_fd;
    struct sockaddr_in address;
    socklen_t address_len;
} ServerSocket;

ServerSocket start_server_socket();
int initialize_client_socket();

#endif //DRIVER_NETWORKING_H
