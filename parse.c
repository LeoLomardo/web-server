#include "parse.h"

extern char *optarg;

Options *parse(int argc, char *argv[]) {
    int opt;

    Options *options = (Options*)malloc(sizeof(Options)); 
    if (options == NULL) {
        perror("[CONSOLE] - Error trying to malloc options.\n");
        exit(EXIT_FAILURE);
    }

    options->background = 0;

    if (argc < 2) {
        printf("[CONSOLE] - Please start the server using the following the usage below.\n");
        printf("Usage: %s -p <port> -l <logfile> -s <statsfile> -r <rootdir> -b\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "p:l:s:r:b")) != -1) {
        switch (opt) {
            case 'p':
                options->port = atoi(optarg);
                break;
            case 'l':
                printf("[CONSOLE] - Log file name is %s.\n", optarg);
                strncpy(options->logFilename, optarg, sizeof(options->logFilename) - 1);
                options->logFilename[sizeof(options->logFilename) - 1] = '\0';
                break;
            case 's':
                printf("[CONSOLE] - Stats file name is %s.\n", optarg);
                strncpy(options->statsFilename, optarg, sizeof(options->statsFilename) - 1);
                options->statsFilename[sizeof(options->statsFilename) - 1] = '\0';
                break;
            case 'r':
                printf("[CONSOLE] - Root directory is %s.\n", optarg);
                strncpy(options->rootDir, optarg, sizeof(options->rootDir) - 1);
                options->rootDir[sizeof(options->rootDir) - 1] = '\0';
                break;
            case 'b':
                printf("[CONSOLE] - Background running set.\n");
                options->background = 1;
                break;
            default:
                printf("Unknown command.\n");
                exit(EXIT_FAILURE);
        }
    }

    return options;
}