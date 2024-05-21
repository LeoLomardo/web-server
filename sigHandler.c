#include "sigHandler.h"

int html_count = 0;
int image_count = 0;
int text_count = 0;
int unknown_count = 0;  

extern Command *command;

void *statisticsPrint(Command *command){
    char *statsFile;
    statsFile = (char *) malloc(strlen(command->logFile) + 1);
    strncpy(statsFile, command->logFile, strlen(command->logFile) + 1);
    statsFile[strlen(command->logFile)] = '\0';
        FILE *statsFile = fopen("stats.txt", "w");
        if (statsFile != NULL) {
            fprintf(statsFile, "HTML: %d\nIMAGEM: %d\nTEXTO: %d\nOUTROS:%d\n", html_count, image_count, text_count);
            fclose(statsFile);
        } else {
            perror("[SERVER] - Failed to open stats.txt\n");
        }

    return NULL;
}


