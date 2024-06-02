#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#include "log.h"
#include "statsInfo.h"
#include "commandHandle.h"
#include "main.h"

void *clientRequest(void *client_sockfd);

#endif
