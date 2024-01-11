#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "misc.h"
#include "logging.h"

int main()
{
    set_log_file_name("client_log");
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        print_errors("Failed opening the socket");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(12345);

    int connection_result = connect(sock, (struct sockaddr*)(&addr), sizeof(addr));
    if(connection_result == -1)
    {
        print_errors("Failed connecting to the server");
        close(sock);
        exit(1);
    }

    char input_buffer[100];
    puts("Enter a request:");
    if(!scanf("%99s", input_buffer))
    {
        print_errors("Reading the request failed");
        close(sock);
        exit(1);
    }

    int send_result = send(sock, input_buffer, strlen(input_buffer), 0);
    if(send_result == -1)
    {
        print_errors("Sending the request failed");
        close(sock);
        exit(1);
    }

    char response_buffer[100];
    int recv_result = recv(sock, response_buffer, 99, 0);
    if(recv_result == -1)
    {
        print_errors("Failed receiving from the connection");
        close(sock);
        exit(1);
    }

    if(memcmp("ERROR\n", response_buffer, 6) == 0)
    {
        puts("Error occurred");
        int log_result = log_error(response_buffer + 6);
        if(log_result < 0)
        {
            if(log_result == -1)
            {
                puts("Log file not initialised");
            }
            else if(log_result == -2)
            {
                puts("Failed opening the log file");
            }
            else if(log_result == -3)
            {
                puts("Failed writing to the log file");
            }
            else
            {
                puts("Unknown error occurred");
            }
        }
        else
        {
            puts("Successfully logged the error");
        }
    }
    else
    {
        puts("Successful communication");
        int log_result = log_response(response_buffer + 6);
        if(log_result < 0)
        {
            if(log_result == -1)
            {
                puts("Log file not initialised");
            }
            else if(log_result == -2)
            {
                puts("Failed opening the log file");
            }
            else if(log_result == -3)
            {
                puts("Failed writing to the log file");
            }
            else
            {
                puts("Unknown error occurred");
            }
        }
        else
        {
            puts("Successfully logged the response");
        }
    }

    close(sock);
}
