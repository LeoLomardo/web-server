#include "main.h"

Command *command;

int main(int argc, char *argv[]) {

    command = extractCommandOptions(argc, argv);

    if (command == NULL){
        fprintf(stderr, "[ERROR] Failed to extract command options\n");
        return EXIT_FAILURE;
    }

    serverRun(command);

    free(command->logFilename);
    free(command->statsFilename);
    free(command->rootDir);
    free(command);
    
    return 0;
}
