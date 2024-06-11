#ifndef COMMAND_HANDLE_C
#define COMMAND_HANDLE_C

typedef struct command {
    char *logFilename;
    char *statsFilename;
    int  port;
    char *rootDir;
    short int background;
} Command;

Command *extractCommandOptions(int argc, char *argv[]);

#endif
