
#ifndef START_SERVER_H
#define START_SERVER_H
#include "log.h"
#include "extractCommandOptions.h"

void serverRun(Command *command);

extern int runningFlag ;
extern int server_sockfd;
extern LogBuffer log_buffer;

#endif