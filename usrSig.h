#ifndef USER_SIG_H
#define USER_SIG_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>  
#include <string.h>
#include <signal.h>

#include "client.h"
#include "log.h"
#include "server.h"

typedef struct {
    int html_count;
    int image_count;
    int text_count;
    char *statsFileName;
} StatsInfo;

extern StatsInfo stats;

void sigHndler(int signal);

#endif
