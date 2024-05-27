#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "log.h"
#include "statsInfo.h"
#include "commandHandle.h"

extern StatsInfo stats;
extern pthread_mutex_t stats_mutex;

void *clientRequest(void *client_sockfd);

#endif
