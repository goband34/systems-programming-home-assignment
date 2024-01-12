#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "response_model.h"

void response_model_fill_with(char *buf, struct response_model *m)
{
    char *parts[2];
    strtok(buf, " ");
    parts[0] = strtok(NULL, " ");
    parts[0]+=3;
    parts[1] = strtok(NULL, " ");
    parts[1]+=3;

    time_t t1 = atoi(parts[0]);
    time_t t2 = atoi(parts[1]);

    m->t2 = t1;
    m->t3 = t2;
}

time_t print_response_model(struct response_model *m)
{
    int delay = ((m->t2 - m->t1) + (m->t3 - m->t4))/2;
    time_t adjusted_time = m->t4 + delay;
    
    printf("Time 1: %s\n", ctime(&(m->t1)));
    printf("Time 2: %s\n", ctime(&(m->t2)));
    printf("Time 3: %s\n", ctime(&(m->t3)));
    printf("Time 4: %s\n", ctime(&(m->t4)));
    printf("Delay: %d\n", delay);
    printf("Final adjusted time: %s\n", ctime(&adjusted_time));

    return adjusted_time;
}

int set_system_time(time_t t)
{
    struct timeval new_time;
    new_time.tv_sec = t;
    new_time.tv_usec = 0;
    return settimeofday(&new_time, NULL);
}
