#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "misc.h"

int main()
{
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

    if(memcmp("ERROR\n", response_buffer, 7) == 0)
    {
        puts("Server responded with an error:");
        puts(response_buffer + 7);
    }
    else
    {
        puts(response_buffer);
    }

    close(sock);
}
