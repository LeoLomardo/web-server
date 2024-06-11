#ifndef COMMAND_HANDLE_C
#define COMMAND_HANDLE_C

typedef struct command {
    short int background;
    int  port;
    char *logFilename;
    char *statsFilename;
    char *rootDir;
} Command;

Command *extractCommandOptions(int argc, char *argv[]);

#endif
