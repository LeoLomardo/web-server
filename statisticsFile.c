#include "statisticsFile.h"

int html_count = 0;
int image_count = 0;
int text_count = 0;
int unknown_count = 0;  

extern Command *command;

void *statisticsPrint(Command *command){
    char *statsFile = (char *) malloc(strlen(command->logFilename) + 1);
    if (statsFile == NULL) {
        fprintf(stderr, "Failed to alocate memory\n");
        return EXIT_FAILURE;
    }
    strncpy(statsFile, command->logFilename, strlen(command->logFilename) + 1);
    statsFile[strlen(command->logFilename)] = '\0';
        FILE *arquivoStats = fopen(statsFile, "w+");
        if (arquivoStats != NULL) {
            fprintf(arquivoStats, "HTML: %d\nIMAGEM: %d\nTEXTO: %d\n", html_count, image_count, text_count);
            fclose(arquivoStats);
        } else {
            fprintf(stderr,"[SERVER] - Failed to open stats.txt\n");
        }

    return NULL;
}


