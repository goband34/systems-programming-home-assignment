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
