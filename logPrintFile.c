#include "log.h"

void *LPrinfFile(void *arg) {
    LogBuffer *buffer = (LogBuffer *)arg;
    FILE *logfile = fopen(buffer->logFile, "a+");
    if (logfile == NULL) {
        perror("Failed to open log file");
        exit(1);
    }

    while (1) {
        pthread_mutex_lock(&buffer->mutex);
        while (buffer->count == 0) {
            pthread_cond_wait(&buffer->cond, &buffer->mutex);
        }
        fputs(buffer->entries[buffer->start], logfile);
        fflush(logfile);
        printf("[LOG] - Wrote log entry: %s\n", buffer->entries[buffer->start]);
        buffer->start = (buffer->start + 1) % MAX_ENTRIES;
        buffer->count--;
        pthread_mutex_unlock(&buffer->mutex);
    }

    fclose(logfile);

    return NULL;
}
