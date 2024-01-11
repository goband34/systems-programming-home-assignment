#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

void print_errors(char *message)
{
    printf("%s with code %d:\n%s", message, errno, strerror(errno));
}

void print_time_human(time_t time)
{
    puts(ctime(&time));
}
