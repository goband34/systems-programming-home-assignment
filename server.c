#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "misc.h"
#include "logging.h"

char log_prefix[] = "Server";

int connection_socket_setup(int sock, struct sockaddr *addr, size_t addr_size)
{
    if(bind(sock, addr, addr_size) == -1)
    {
        generalised_log(log_prefix, strerror(errno), LOG_ERROR);
        return -1;
    }

    if(listen(sock, 1) == -1)
    {
        generalised_log(log_prefix, strerror(errno), LOG_ERROR);
        return -2;
    }

    return 1;
}

int main_loop(int sock, struct sockaddr *addr, socklen_t *addr_size, char *input_buffer)
{
    while(1)
    {
        int client_sock = accept(sock, addr, addr_size);

        if(client_sock == -1)
        {
            if(errno != EAGAIN && errno != EWOULDBLOCK)
            {
                puts("Main loop failure, check the logs");
                generalised_log(log_prefix, strerror(errno), LOG_ERROR);
                return -1;
            }
        }
        else
        {
            puts("Client connected");
            if(recv(client_sock, input_buffer, 99, 0) == -1)
            {
                puts("Server error, check the logs");
                generalised_log(log_prefix, strerror(errno), LOG_ERROR);
                close(client_sock);
                return -1;
            }

            // artificial delay
            sleep(5);

            unsigned long recv_time = time(NULL);

            generalised_log(log_prefix, input_buffer, LOG_RECEIVE);
            if(strcmp(input_buffer, "GETTIME") == 0)
            {
                // artificial delay
                sleep(5);

                unsigned long resp_time = time(NULL);

                // TODO: See if it's reasonable to make the buffer smaller
                char response[200];
                sprintf(response, "TIME t1:%ld t2:%ld\n", recv_time, resp_time);
                if(send(client_sock, response, strlen(response)+1, 0) == -1)
                {
                    puts("Server error, check the logs");
                    generalised_log(log_prefix, strerror(errno), LOG_ERROR);
                    close(client_sock);
                    return -1;
                }
                
                generalised_log(log_prefix, response, LOG_SEND);
            }
            else
            {
                char response[] = "ERROR\nInvalid Message\n";
                if(send(client_sock, response, strlen(response)+1, 0) == -1)
                {
                    puts("Server error, check the logs");
                    generalised_log(log_prefix, strerror(errno), LOG_ERROR);
                    close(client_sock);
                    return -1;
                }

                generalised_log(log_prefix, response, LOG_SEND);
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

int main(int argc, char **argv)
{
    if(argc > 1)
    {
        for(size_t i = 1; i < argc; i++)
        {
            if(strcmp(argv[i], "--log") == 0)
            {
                set_log_file_path(argv[i+1]);
            }
        }
    }

    int connection_sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if(connection_sock == -1)
    {
        generalised_log(log_prefix, strerror(errno), LOG_ERROR);
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(12345);
    socklen_t addr_size = sizeof(addr);

    if(connection_socket_setup(connection_sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        close(connection_sock);
        exit(1);
    }

    char input_buffer[100];
    int r = main_loop(connection_sock, (struct sockaddr*)&addr, &addr_size, input_buffer);

    close(connection_sock);
    if(r < 0)
    {
        return 1;
    }
}
