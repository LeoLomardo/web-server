
#ifndef START_SERVER_H
#define START_SERVER_H

#include "log.h"
#include "extractCommandOptions.h"

extern LogBuffer log_buffer;
extern int runningFlag ;
extern int server_sockfd;
extern char *client_ip;

void serverRun(Command *command);

#endif