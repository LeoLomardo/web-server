#ifndef LOG_H
#define LOG_H

#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

//VALORES ARBITRÁRIOS
#define MAX_ENTRIES 200
#define LOG_SIZE 2048
#define LOG_FILE_NAME_SIZE 128

typedef struct {
    char entries[MAX_ENTRIES][LOG_SIZE];
    int start;
    int end;
    int count;
    int size;
    char *logFile;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} LogBuffer;

void LBufferInit(LogBuffer *buffer, const char *filename);
void LEntry(LogBuffer *buffer, const char *entry);
void *LPrinfFile(void *arg);
void LBufferFree(LogBuffer *buffer);

#endif
