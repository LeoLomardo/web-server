#include "main.h"

Command *command = NULL;

int main(int argc, char *argv[]) {

    command = extractCommandOptions(argc, argv);
    serverRun(command);
    
    return 0;
}
