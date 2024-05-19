#include "log.h"

void LBufferInit(LogBuffer *buffer, const char *filename) {
    buffer->start = 0;
    buffer->end = 0;
    buffer->count = 0;
    buffer->size = LOG_SIZE;

    // Alocar memória para logFile e copiar o nome do arquivo
    buffer->logFile = (char *)malloc(strlen(filename) + 1); // +1 para o caractere nulo
    if (buffer->logFile == NULL) {
        perror("Failed to allocate memory for logFile");
        exit(1);
    }
    strcpy(buffer->logFile, filename);

    pthread_mutex_init(&buffer->mutex, NULL);
    pthread_cond_init(&buffer->cond, NULL);
}
