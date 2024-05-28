#ifndef SIGHANDLER_H
#define SIGHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

typedef struct {
    int html_count;
    int image_count;
    int text_count;
    char *statsFileName;
    pthread_mutex_t stats_mutex;
} StatsInfo;

void *statisticsPrint(StatsInfo stats);

#endif