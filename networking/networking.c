/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include <stdio.h> //for perror
#include <stdlib.h> //for exit
#include <arpa/inet.h> //for inet pton

#include "networking.h"

ServerSocket start_server_socket()
{
    int server_fd;
    int opt = 1;
    struct sockaddr_in address;
    socklen_t address_len = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return (ServerSocket){.server_fd=server_fd, .address=address, .address_len=address_len};
}

int initialize_client_socket()
{
    int status, client_fd;
    struct sockaddr_in serv_addr;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("\n Socket creation error \n");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        perror(
                "\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }

    if ((status
                 = connect(client_fd, (struct sockaddr*)&serv_addr,
                           sizeof(serv_addr)))
        < 0) {
        perror("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
    return client_fd;
}

