#include "extractCommandOptions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

Command *extractCommandOptions(int argc, char *argv[]){
    Command *command = (Command *)malloc(sizeof(Command));
    if(command == NULL){
        fprintf(stderr, "extractCommandOptions - Error alocating memory.\n");
        exit(EXIT_FAILURE);
    }

    command->background = 0;
    command->port = 0;
    command->logFilename = NULL;
    command->statsFilename = NULL;
    command->rootDir = NULL;

    if(argc < 2){
        printf("extractCommandOptions -  Error number of arguments\n");
        printf("Format: %s -p <port> -l <logfile> -s <statsfile> -r <rootdir> -b\n", argv[0]);
        free(command);
        exit(EXIT_FAILURE);
    }
   struct option long_options[] = {
        {"port", required_argument, 0, 'p'},
        {"log", required_argument, 0, 'l'},
        {"statistics", required_argument, 0, 's'},
        {"background", no_argument, 0, 'b'},
        {"root", required_argument, 0, 'r'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    while((opt = getopt_long(argc, argv, "p:l:s:r:b", long_options, &option_index)) != -1){
        switch (opt){
            case 'p':
                command->port = atoi(optarg);
                break;
            case 'l':
                printf("extractCommandOptions - Log file name is %s\n", optarg);
                command->logFilename = (char *)malloc(strlen(optarg) + 1);
                if(command->logFilename == NULL){
                    fprintf(stderr, "extractCommandOptions - Error allocating memory for logFilename.\n");
                    free(command);
                    exit(EXIT_FAILURE);
                }
                strcpy(command->logFilename, optarg);
                break;
            case 's':
                printf("extractCommandOptions - Stats file name is %s\n", optarg);
                command->statsFilename = (char *)malloc(strlen(optarg) + 1);
                if(command->statsFilename == NULL){
                    fprintf(stderr, "extractCommandOptions - Error allocating memory for statsFilename.\n");
                    free(command->logFilename);
                    free(command);
                    exit(EXIT_FAILURE);
                }
                strcpy(command->statsFilename, optarg);
                break;
            case 'r':
                printf("extractCommandOptions - Root directory is %s\n", optarg);
                command->rootDir = (char *)malloc(strlen(optarg) + 1);
                if(command->rootDir == NULL){
                    fprintf(stderr, "extractCommandOptions - Error allocating memory for rootDir.\n");
                    free(command->logFilename);
                    free(command->statsFilename);
                    free(command);
                    exit(EXIT_FAILURE);
                }
                strcpy(command->rootDir, optarg);
                break;
            case 'b':
                printf("extractCommandOptions - Running with background flag == 1\n");
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
