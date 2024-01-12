#include <stdio.h>
#include <string.h>
#include "logging.h"

// Max linux path length and null terminator
char log_file_path[4097] = DEFAULT_LOG_FILE_PATH;

void set_log_file_path(char *path)
{
    strncpy(log_file_path, path, 4097);
}

// Assume content formatted
int log_receive(char *prefix, char *content)
{
    FILE *fp = fopen(log_file_path, "a");
    if(fp == NULL)
    {
        return -1;
    }

    if(fprintf(fp, "%s RECEIVE: %s\n", prefix, content) < 0)
    {
        return -2;
    }

    fclose(fp);
    return 1;
}

// Assume content formatted
int log_send(char *prefix, char *content)
{
    FILE *fp = fopen(log_file_path, "a");
    if(fp == NULL)
    {
        return -1;
    }

    if(fprintf(fp, "%s SEND: %s\n", prefix, content) < 0)
    {
        return -2;
    }

    fclose(fp);
    return 1;
}

// Assume error formatted
int log_error(char *prefix, char *error)
{
    FILE *fp = fopen(log_file_path, "a");
    if(fp == NULL)
    {
        return -1;
    }

    if(fprintf(fp, "%s ERROR: %s\n", prefix, error) < 0)
    {
        return -2;
    }

    fclose(fp);
    return 1;
}

int generalised_log(char *prefix, char *buf, short log_type)
{
    int log_result;
    switch(log_type) {
    case LOG_RECEIVE:
        log_result = log_receive(prefix, buf);
        break;
    case LOG_SEND:
        log_result = log_send(prefix, buf);
        break;
    case LOG_ERROR:
        log_result = log_error(prefix, buf);
        break;
    default:
        return -1;
    }

    if(log_result < 0)
    {
        if(log_result == -1)
        {
            puts("Failed opening the log file");
        }
        else if(log_result == -2)
        {
            puts("Failed writing to the log file");
        }
        else
        {
            puts("Unknown error occurred");
        }

        return log_result;
    }
    
    return 1;
}
