#ifndef LOG_H
#define LOG_H

#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define MAX_LOG_ENTRIES 100

typedef struct {
    char entries[MAX_LOG_ENTRIES][1024];
    int start;
    int end;
    int count;
    int size;
    char log_filename[256];
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} LogBuffer;

void init_log_buffer(LogBuffer *buffer, const char *filename);
void add_log_entry(LogBuffer *buffer, const char *entry);
void *log_writer(void *arg);
void log_request(LogBuffer *buffer, const char *filename);
#endif

