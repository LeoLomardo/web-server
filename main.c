#include "extractCommandOptions.h"
#include "serverRun.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    Command *command = extractCommandOptions(argc, argv);
    if(command == NULL){
        fprintf(stderr, "main - Error extracting command options\n");
        return EXIT_FAILURE;
    }

    serverRun(command);
    free(command->rootDir);
    free(command);
    return 0;
}
