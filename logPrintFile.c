#include "log.h"

FILE *logFile;

void *LPrinfFile(void *arg){
    LogBuffer *buffer = (LogBuffer *)arg;

    logFile = fopen(buffer->logFile, "a+");

    while(1){
        pthread_mutex_lock(&buffer->mutex);
        while (buffer->count == 0){
            pthread_cond_wait(&buffer->cond, &buffer->mutex);
        }
        fputs(buffer->entries[buffer->start], logFile);
        fflush(logFile);
        printf("LPrinfFile - Successfully wrote log entry: %s on file %s\n", buffer->entries[buffer->start], buffer->logFile);
        buffer->start = (buffer->start + 1) % MAX_ENTRIES;
        buffer->count--;
        pthread_mutex_unlock(&buffer->mutex);
    }
    return NULL;
}
