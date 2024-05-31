#include "log.h"

void LBufferInit(LogBuffer *buffer, const char *filename) {
    buffer->start = 0;
    buffer->end = 0;
    buffer->count = 0;
    buffer->size = MAX_BUFFER_SIZE;
    buffer->logFile = (char *)malloc(strlen(filename) + 1); 
    if (buffer->logFile == NULL) {
        fprintf(stderr,"Failed to allocate memory for logFile\n");
        exit(EXIT_FAILURE);
    }
    strcpy(buffer->logFile, filename);
    //buffer->logFile[sizeof(buffer->logFile) - 1] = '\0';
    
    pthread_mutex_init(&buffer->mutex, NULL);
    pthread_cond_init(&buffer->cond, NULL);
}
