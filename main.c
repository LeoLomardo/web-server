#include "main.h"

int main(int argc, char *argv[]) {
    Command *command = extractCommandOptions(argc, argv);
    serverRun(command);

    //signal(SIGUSR1, sigHandler);
    return 0;
}
