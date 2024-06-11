#include "main.h"

int main(int argc, char *argv[]){

    Command *command = extractCommandOptions(argc, argv);
    if(command == NULL){
        fprintf(stderr, "main - Error extracting command options\n");
        return EXIT_FAILURE;
    }
    serverRun(command);
    /*
    * Tive problemas em liberar a memoria alocada para a string contendo o nome do diretorio raiz
    */
    free(command->rootDir);
    free(command);
    return 0;
}
