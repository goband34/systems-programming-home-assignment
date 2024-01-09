#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "misc.h"

int main()
{
    int connection_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(connection_sock == -1)
    {
        print_errors("Failed opening the socket");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(12345);

    int bind_result = bind(connection_sock, (struct sockaddr*)&addr, sizeof(addr));
    if(bind_result == -1)
    {
        print_errors("Failed binding");
        close(sock);
        exit(1);
    }
    
    int listen_sock = accept(sock, (struct sockaddr*)&addr, sizeof(addr));
    if(listen_sock == -1)
    {
        print_errors("Failed accepting to the server");
        close(sock);
        exit(1);
    }

    char input_buffer[100];
    int recv_result = recv(listen_sock, input_buffer, 99, 0);
    if(recv_result == -1)
    {
        print_errors("Failed receiving from the connection");
        close(sock);
        exit(1);
    }

    puts(input_buffer);
    close(sock);
}
