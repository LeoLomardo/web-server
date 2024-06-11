
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
#include <errno.h> //errno new_socket

#include "log.h"
#include "client.h" // funcao clientRequest
#include "usrSig.h"
#include "commandHandle.h"

void serverRun(Command *command);

extern int runningFlag ;
extern int server_sockfd;
extern LogBuffer log_buffer;

#endif