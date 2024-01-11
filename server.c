#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "misc.h"

int main()
{
    int connection_sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if(connection_sock == -1)
    {
        print_errors("Failed opening the socket");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(12345);
    socklen_t addr_size = sizeof(addr);

    if(bind(connection_sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        print_errors("Failed binding");
        close(connection_sock);
        exit(1);
    }

    if(listen(connection_sock, 1) == -1)
    {
        print_errors("Failed listening");
        close(connection_sock);
        exit(1);
    }

    char input_buffer[100];
    while(1)
    {
        int client_sock = accept(connection_sock, (struct sockaddr*)&addr, &addr_size);

        if(client_sock == -1)
        {
            if(errno != EAGAIN && errno != EWOULDBLOCK)
            {
                print_errors("Main loop failure");
                close(connection_sock);
                exit(1);
            }
        }
        else
        {
            puts("Client connected");
            if(recv(client_sock, input_buffer, 99, 0) == -1)
            {
                print_errors("Failed receiving from the connection");
                close(client_sock);
                close(connection_sock);
                exit(1);
            }

            unsigned long recv_time = time(NULL);

            printf("Received message from client: %s\n", input_buffer);
            if(strcmp(input_buffer, "GETTIME") == 0)
            {
                unsigned long resp_time = time(NULL);
                // TODO: See if it's reasonable to make the buffer smaller
                char response[200];
                sprintf(response, "Time t1:%ld t2:%ld", recv_time, resp_time);
                if(send(client_sock, response, strlen(response), 0) == -1)
                {
                    print_errors("Failed sending a reply");
                    close(client_sock);
                    close(connection_sock);
                    exit(1);
                }
            }
            else
            {
                char response[] = "Error\nInvalid Message\n";
                if(send(client_sock, response, strlen(response), 0) == -1)
                {
                    print_errors("Failed sending a reply");
                    close(client_sock);
                    close(connection_sock);
                    exit(1);
                }
            }

            memset(input_buffer, 0, 99);
            close(client_sock);
        }

        // Was getting really high CPU usage so hoping this offsets it
        // Real code would use select/epoll/whatever, but that's too much
        // for the assignment
        sleep(1);
    }
}
