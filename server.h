
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
#include <signal.h>
#include <netdb.h>

#include "log.h"
#include "client.h"
#include "statsInfo.h"
#include "usrSig.h"
#define BACKLOG 10

void serverRun(Command *command);

#endif