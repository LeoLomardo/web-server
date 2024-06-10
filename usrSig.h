#ifndef USER_SIG_H
#define USER_SIG_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>  
#include <string.h>

#include "client.h"

typedef struct {
    int html_count;
    int image_count;
    int text_count;
    char *statsFileName;
} StatsInfo;

void sigHndler(int signal);

#endif
