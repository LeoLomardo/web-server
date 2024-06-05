#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include "commandHandle.h"
#include "usrSig.h"

//VALORES ARBITRARIOS
#define MAX_ENTRIES 200
#define MAX_BUFFER_SIZE 70000

typedef struct logbuffer{
    int start;
    int end;
    int count;
    int size;
    char entries[MAX_ENTRIES][MAX_BUFFER_SIZE];
    char *logFile;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} LogBuffer;

void LBufferInit(LogBuffer *buffer, const char *filename);
void LEntry(LogBuffer *buffer, const char *entry);
void *LPrinfFile(void *arg);

#endif
