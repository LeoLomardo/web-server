
#ifndef START_SERVER_H
#define START_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <arpa/inet.h>

#include "commandHandle.h"
#include "log.h"
#include "client.h"
#include "sigHandler.h"

extern int html_count; 
extern int image_count;
extern int text_count;


void serverRun(Command *command);

#endif