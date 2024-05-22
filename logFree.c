#include "log.h"

void LBufferFree(LogBuffer *buffer) {
    free(buffer);
    pthread_mutex_destroy(&buffer->mutex);
    pthread_cond_destroy(&buffer->cond);
}
