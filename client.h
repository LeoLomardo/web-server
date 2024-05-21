#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "log.h"
#include "globais.h"

void *clientRequest(void *client_sockfd);

#endif
