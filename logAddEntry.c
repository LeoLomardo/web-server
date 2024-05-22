#include "log.h"

void LEntry(LogBuffer *buffer, const char *entry) {
    pthread_mutex_lock(&buffer->mutex);
    if (buffer->count < MAX_ENTRIES) {
        strncpy(buffer->entries[buffer->end], entry, sizeof(buffer->entries[buffer->end]) - 1);
        buffer->entries[buffer->end][sizeof(buffer->entries[buffer->end]) - 1] = '\0';
        buffer->end = (buffer->end + 1) % MAX_ENTRIES;
        buffer->count++;
        pthread_cond_signal(&buffer->cond);
        printf("[LOG] - Added log entry: %s\n", entry);
    } else {
        fprintf(stderr, "[LOG] - Log buffer full, entry discarded: %s\n", entry);
        exit(EXIT_FAILURE);
    }
    pthread_mutex_unlock(&buffer->mutex);
}
