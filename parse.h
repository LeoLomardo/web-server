
#ifndef PARSE_OPTIONS_H
#define PARSE_OPTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct options {
    int port;
    char logFilename[256];
    char statsFilename[256];
    char rootDir[256];
    int background;
} Options;

Options *parse(int argc, char *argv[]);

#endif