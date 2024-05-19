#ifndef SIG_HANDLER_H
#define SIG_HANDLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void *handle_client(void *client_sockfd);

#endif