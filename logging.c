#include <stdio.h>
#include <string.h>

short log_file_init = 0;
char log_file_name[100];

// Relative name
int set_log_file_name(char *name)
{
    if(strlen(name) > 99)
    {
        return -1;
    }

    strcpy(log_file_name, name);
    log_file_init = 1;
    return 1;
}

// Assume response formatted
int log_response(char *response)
{
    if(!log_file_init)
    {
        return -1;
    }

    // Max length supported by Linux + 1, might be an overkill
    char file_path[4097];
    sprintf(file_path, "%s/logs/%s", ROOT_DIR, log_file_name); 

    FILE *fp = fopen(file_path, "a");
    if(fp == NULL)
    {
        return -2;
    }

    if(fprintf(fp, "RESPONSE: %s\n", response) < 0)
    {
        return -3;
    }

    fclose(fp);
    return 1;
}

// Assume request formatted
int log_request(char *request)
{
    if(!log_file_init)
    {
        return -1;
    }

    // Max length supported by Linux + 1, might be an overkill
    char file_path[4097];
    sprintf(file_path, "%s/logs/%s", ROOT_DIR, log_file_name); 

    FILE *fp = fopen(file_path, "a");
    if(fp == NULL)
    {
        return -2;
    }

    if(fprintf(fp, "REQUEST: %s\n", request) < 0)
    {
        return -3;
    }

    fclose(fp);
    return 1;
}

// Assume error formatted
int log_error(char *error)
{
    if(!log_file_init)
    {
        return -1;
    }

    // Max length supported by Linux + 1, might be an overkill
    char file_path[4097];
    sprintf(file_path, "%s/logs/%s", ROOT_DIR, log_file_name); 

    FILE *fp = fopen(file_path, "a");
    if(fp == NULL)
    {
        return -2;
    }

    if(fprintf(fp, "ERROR: %s\n", error) < 0)
    {
        return -3;
    }

    fclose(fp);
    return 1;
}

