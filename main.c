#include "main.h"

Command *command;

int main(int argc, char *argv[]) {

    command = extractCommandOptions(argc, argv);

    if (command == NULL) {
        fprintf(stderr, "[ERROR] Failed to extract command options\n");
        return EXIT_FAILURE;
    }

    serverRun(command);
    free(command); 
    //pthread_mutex_destroy(&stats.stats_mutex);
    return 0;
}
