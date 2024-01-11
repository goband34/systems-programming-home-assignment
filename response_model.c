#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

void print_response_model(struct response_model *m)
{
    // BUG: Time not being printed properly for some reason
    // Different timestamps but same time
    printf("Time 1: %d\nTime 2: %d\nTime 3: %d\nTime 4: %d\n", m->t1, m->t2, m->t3, m->t4);
    printf("Time 1: %s\nTime 2: %s\nTime 3: %s\nTime 4: %s\n", ctime(&(m->t1)), ctime(&(m->t2)), ctime(&(m->t3)), ctime(&(m->t4)));
}
