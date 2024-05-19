#include "log.h"

void LBufferDestroy(LogBuffer *buffer) {
    free(buffer->logFile);
    pthread_mutex_destroy(&buffer->mutex);
    pthread_cond_destroy(&buffer->cond);
}
