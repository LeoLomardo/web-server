#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> //pega data e hora
#include <sys/stat.h> //pega ultima modificacao e tamanho do arquivo
#include <unistd.h> //read write close
#include <fcntl.h>
#include <arpa/inet.h>

#include "usrSig.h" // precisa pela struct statsInfo
#include "log.h" // precisa pela struct logBuffer
void *clientRequest(void *client_sockfd);


#endif
