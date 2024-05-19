#include "log.h"

void log_request(LogBuffer *buffer, const char *filename) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char log_entry[256];

    snprintf(log_entry, 256, "%04d-%02d-%02d %02d:%02d:%02d %s", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, filename);

    pthread_mutex_lock(&buffer->mutex);

    if (buffer->count < buffer->size) {
        strcpy(buffer->entries[buffer->end], log_entry);
        buffer->end = (buffer->end + 1) % buffer->size;
        buffer->count++;
        pthread_cond_signal(&buffer->cond);
    }

    pthread_mutex_unlock(&buffer->mutex);
}
