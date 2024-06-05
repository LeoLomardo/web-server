#include "commandHandle.h"

Command *extractCommandOptions(int argc, char *argv[]){
    Command *command = (Command *)malloc(sizeof(Command));
    if(command == NULL){
        fprintf(stderr, "commandHandler - Error alocating memory.\n");
        exit(EXIT_FAILURE);
    }

    command->background = 0;
    command->port = 0;
    command->logFilename = NULL;
    command->statsFilename = NULL;
    command->rootDir = NULL;

    if(argc < 2){
        printf("commandHandler -  Error number of arguments\n");
        printf("Format: %s -p <port> -l <logfile> -s <statsfile> -r <rootdir> -b\n", argv[0]);
        free(command);
        exit(EXIT_FAILURE);
    }
    int opt;
    while((opt = getopt(argc, argv, "p:l:s:r:b")) != -1){
        switch (opt){
            case 'p':
                command->port = atoi(optarg);
                break;
            case 'l':
                printf("commandHandler - Log file name is %s\n", optarg);
                command->logFilename = (char *)malloc(strlen(optarg) + 1);
                if(command->logFilename == NULL){
                    fprintf(stderr, "commandHandler - alocating memory for logFilename.\n");
                    free(command);
                    exit(EXIT_FAILURE);
                }
                strcpy(command->logFilename, optarg);
                break;
            case 's':
                printf("commandHandler - Stats file name is %s\n", optarg);
                command->statsFilename = (char *)malloc(strlen(optarg) + 1);
                if(command->statsFilename == NULL){
                    fprintf(stderr, "commandHandler - Error alocating memory for statsFilename.\n");
                    free(command->logFilename);
                    free(command);
                    exit(EXIT_FAILURE);
                }
                strcpy(command->statsFilename, optarg);
                break;
            case 'r':
                printf("commandHandler - Root directory is %s \n", optarg);
                command->rootDir = (char *)malloc(strlen(optarg) + 1);
                if(command->rootDir == NULL){
                    fprintf(stderr, "commandHandler - Error alocating memory for rootDir.\n");
                    free(command->logFilename);
                    free(command->statsFilename);
                    free(command);
                    exit(EXIT_FAILURE);
                }
                strcpy(command->rootDir, optarg);
                break;
            case 'b':
                printf("commandHandler - Running wit background flag == 1\n");
                command->background = 1;
                break;
            default:
                fprintf(stderr, "Unknown command\n");
                free(command->logFilename);
                free(command->statsFilename);
                free(command->rootDir);
                free(command);
                exit(EXIT_FAILURE);
        }
    }
    return command;
}

