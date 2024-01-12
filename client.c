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
#include "response_model.h"

char log_prefix[] = "Client";
struct response_model response_model;

int send_request_to_server(int sock, struct sockaddr *addr, size_t addr_size, char *response_buffer, size_t response_buffer_size)
{
    if(connect(sock, addr, addr_size) == -1)
    {
        generalised_log(log_prefix, strerror(errno), LOG_ERROR);
        return -1;
    }

    char input_buffer[100];
    puts("Enter a request:");
    if(!scanf("%99s", input_buffer))
    {
        generalised_log(log_prefix, strerror(errno), LOG_ERROR);
        return -2;
    }
    response_model.t1 = time(NULL);
    if(send(sock, input_buffer, strlen(input_buffer), 0) == -1)
    {
        generalised_log(log_prefix, strerror(errno), LOG_ERROR);
        return -3;
    }
    generalised_log(log_prefix, input_buffer, LOG_SEND);

    if(recv(sock, response_buffer, response_buffer_size, 0) == -1)
    {
        generalised_log(log_prefix, strerror(errno), LOG_ERROR);
        return -4;
    }
    response_model.t4 = time(NULL);
    generalised_log(log_prefix, response_buffer, LOG_RECEIVE);

    ensure_string_terminated(response_buffer, response_buffer_size);

    return 1;
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

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        puts("Client error, check the logs");
        generalised_log(log_prefix, strerror(errno), LOG_ERROR);
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(12345);

    char response_buffer[100];
    int send_result = send_request_to_server(sock, (struct sockaddr*)&addr, sizeof(addr), response_buffer, 100);
    if(send_result < 0)
    {
        puts("Client error, check the logs");
        close(sock);
        exit(1);
    }

    if(!is_error_response(response_buffer))
    {
        response_model_fill_with(response_buffer, &response_model);
        #ifdef FULL_VERSION
        time_t updated_time = print_response_model(&response_model);
        if(set_system_time(updated_time) == 0)
        {
            puts("Successfully set the system time");
        }
        else
        {
            puts("Client error, check the logs");
            generalised_log(log_prefix, strerror(errno), LOG_ERROR);
        }
        #else
        print_response_model(&response_model);
        #endif
    }
    else
    {
        puts("Server responded with an error, check the logs");
    }

    close(sock);
}
