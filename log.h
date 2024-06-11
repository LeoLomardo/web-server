#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <pthread.h>

//adicionei apenas para ficar visualmente mais facil do usuario ver o comando
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

//VALORES ARBITRARIOS
#define MAX_ENTRIES 200
#define MAX_BUFFER_SIZE 70000

typedef struct logbuffer{
    char entries[MAX_ENTRIES][MAX_BUFFER_SIZE];
    char *logFile;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int start;
    int end;
    int count;
    int size;
} LogBuffer;

void LBufferInit(LogBuffer *buffer, const char *filename);
void LEntry(LogBuffer *buffer, const char *entry);
void *LPrinfFile(void *arg);

extern FILE *logFile;
extern LogBuffer log_buffer;

#endif
