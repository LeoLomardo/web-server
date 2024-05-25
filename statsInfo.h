#ifndef SIGHANDLER_H
#define SIGHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "commandHandle.h"


typedef struct {
    int html_count;
    int image_count;
    int text_count;
} StatsInfo;

void *statisticsPrint(StatsInfo stats);
void initStats(StatsInfo stats, const char *filename);

#endif