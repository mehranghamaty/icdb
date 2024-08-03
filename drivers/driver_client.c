/**
 * This file is copyrighted by Meandering LLC 2023
 */
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../networking/networking.h"

int read_input(char* buffer)
{
    scanf("%s", buffer);
    printf("%s", buffer);
    return 1;
}

static volatile int running = 1;

void intHandler(int signal) {
    printf("got signal %d", signal);
    running = 0;
}


int main(int argc, char const* argv[])
{
    ssize_t amount_read;
    int client_fd;
    char* hello = "PUT 5";
    char received_buffer[1024] = { 0 };

    client_fd = initialize_client_socket();

    while(running) {
        int i = 0;
        char sending_buffer[1024] = { 0 };
        printf("Type a command:\n");
        char ch;
        while(read(STDIN_FILENO, &ch, 1) > 0)
        {
            sending_buffer[i++] = ch;
            if(ch == '\n') {
                break;
            }
        }

        send(client_fd, sending_buffer, strlen(sending_buffer), 0);
        printf("Hello message sent\n");
        amount_read = read(client_fd, received_buffer, 1024 - 1); // subtract 1 for the null terminator at the end
        printf("%s\n", received_buffer);
    }

    // closing the connected socket
    close(client_fd);
    return 0;
}
