#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void ensure_string_terminated(char *buf, size_t buf_len)
{
    for(size_t i = 0; i < buf_len; i++)
    {
        if(buf[i] == '\0')
        {
            return;
        }
    }

    buf[buf_len-1] = '\0';
}

short is_error_response(char *buf)
{
    return memcmp(buf, "ERROR\n", 6) == 0;
}

char* get_error_message(char *buf)
{
    return buf+6;
}

void print_time_response(char *buf)
{
    char *parts[3];
    parts[0] = strtok(buf, " ");
    parts[1] = strtok(NULL, " ");
    parts[1]+=3;
    parts[2] = strtok(NULL, " ");
    parts[2]+=3;

    time_t t1 = atoi(parts[1]);
    time_t t2 = atoi(parts[2]);

    printf("Time 1 raw: %s\nTime 1 human: %s\nTime 2 raw: %s\nTime 2 formatted: %s\n", parts[1], ctime(&t1), parts[2], ctime(&t2));
}
