
#ifndef PARSE_H
#define PARSE_H

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

Command *parse(int argc, char *argv[]);

#endif