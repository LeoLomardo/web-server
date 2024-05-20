#include "commandHandle.h"

extern char *optarg;

Command *extractCommandOptions(int argc, char *argv[]) {
    int opt;

    Command *command = (Command*)malloc(sizeof(Command)); 
    if (command == NULL) {
        perror("[CONSOLE] - Error trying to malloc command.\n");
        exit(EXIT_FAILURE);
    }

    command->background = 0;

    if (argc < 2) {
        printf("[CONSOLE] - Please start the server using the following the usage below.\n");
        printf("Usage: %s -p <port> -l <logfile> -s <statsfile> -r <rootdir> -b\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "p:l:s:r:b")) != -1) {
        switch (opt) {
            case 'p':
                command->port = atoi(optarg);
                break;
            case 'l':
                printf("[CONSOLE] - Log file name is %s.\n", optarg);
                strncpy(command->logFilename, optarg, sizeof(command->logFilename) - 1);
                command->logFilename[sizeof(command->logFilename) - 1] = '\0';
                break;
            case 's':
                printf("[CONSOLE] - Stats file name is %s.\n", optarg);
                strncpy(command->statsFilename, optarg, sizeof(command->statsFilename) - 1);
                command->statsFilename[sizeof(command->statsFilename) - 1] = '\0';
                break;
            case 'r':
                printf("[CONSOLE] - Root directory is %s.\n", optarg);
                strncpy(command->rootDir, optarg, sizeof(command->rootDir) - 1);
                command->rootDir[sizeof(command->rootDir) - 1] = '\0';
                break;
            case 'b':
                printf("[CONSOLE] - Background running set.\n");
                command->background = 1;
                break;
            default:
                printf("Unknown command.\n");
                exit(EXIT_FAILURE);
        }
    }

    return command;
}