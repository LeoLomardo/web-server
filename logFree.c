#include "log.h"

void LBufferFree(LogBuffer *buffer) {
    
    pthread_mutex_destroy(&buffer->mutex);
    pthread_cond_destroy(&buffer->cond);
    free(buffer);
}
