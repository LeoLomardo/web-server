#include "commandHandle.h"

Command *extractCommandOptions(int argc, char *argv[]) {
    int opt;

    Command *command = (Command *)malloc(sizeof(Command));
    if (command == NULL) {
        fprintf(stderr, "[CONSOLE] - Error trying to malloc command.\n");
        exit(EXIT_FAILURE);
    }

    command->background = 0;
    command->port = 0;
    command->logFilename = NULL;
    command->statsFilename = NULL;
    command->rootDir = NULL;

    if (argc < 2) {
        printf("[CONSOLE] - Please start the server using the following usage below.\n");
        printf("Usage: %s -p <port> -l <logfile> -s <statsfile> -r <rootdir> -b\n", argv[0]);
        free(command);
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "p:l:s:r:b")) != -1) {
        switch (opt) {
            case 'p':
                command->port = atoi(optarg);
                break;
            case 'l':
                printf("[CONSOLE] - Log file name is %s.\n", optarg);
                command->logFilename = (char *)malloc(strlen(optarg) + 1);
                if (command->logFilename == NULL) {
                    fprintf(stderr, "[CONSOLE] - Error trying to malloc logFilename.\n");
                    free(command);
                    exit(EXIT_FAILURE);
                }
                strcpy(command->logFilename, optarg);
                break;
            case 's':
                printf("[CONSOLE] - Stats file name is %s.\n", optarg);
                command->statsFilename = (char *)malloc(strlen(optarg) + 1);
                if (command->statsFilename == NULL) {
                    fprintf(stderr, "[CONSOLE] - Error trying to malloc statsFilename.\n");
                    free(command->logFilename);
                    free(command);
                    exit(EXIT_FAILURE);
                }
                strcpy(command->statsFilename, optarg);
                break;
            case 'r':
                printf("[CONSOLE] - Root directory is %s.\n", optarg);
                command->rootDir = (char *)malloc(strlen(optarg) + 1);
                if (command->rootDir == NULL) {
                    fprintf(stderr, "[CONSOLE] - Error trying to malloc rootDir.\n");
                    free(command->logFilename);
                    free(command->statsFilename);
                    free(command);
                    exit(EXIT_FAILURE);
                }
                strcpy(command->rootDir, optarg);
                break;
            case 'b':
                printf("[CONSOLE] - Background running set.\n");
                command->background = 1;
                break;
            default:
                fprintf(stderr, "Unknown command.\n");
                free(command->logFilename);
                free(command->statsFilename);
                free(command->rootDir);
                free(command);
                exit(EXIT_FAILURE);
        }
    }

    return command;
}