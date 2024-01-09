#include <stdio.h>
#include <errno.h>
#include <string.h>

void print_errors(char *message)
{
    printf("%s with code %d:\n%s", message, errno, strerror(errno));
}
