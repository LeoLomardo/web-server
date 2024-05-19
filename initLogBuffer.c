#include "log.h"

void init_log_buffer(LogBuffer *buffer, const char *filename) {
    buffer->start = 0;
    buffer->end = 0;
    buffer->count = 0;
    buffer->size = 1024;
    strncpy(buffer->log_filename, filename, sizeof(buffer->log_filename) - 1);
    buffer->log_filename[sizeof(buffer->log_filename) - 1] = '\0';
    pthread_mutex_init(&buffer->mutex, NULL);
    pthread_cond_init(&buffer->cond, NULL);
}
