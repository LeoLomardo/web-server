#ifndef COMMAND_HANDLE_C
#define COMMAND_HANDLE_C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct command {
    int port;
    char logFilename[256];
    char statsFilename[256];
    char rootDir[256];
    int background;
} Command;


Command *extractCommandOptions(int argc, char *argv[]);

#endif
