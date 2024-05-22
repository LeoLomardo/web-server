#include "main.h"



// int html_count = 0;
// int image_count = 0;
// int text_count = 0;
char *testes = "./testes.sh";

int main(int argc, char *argv[]) {
    Command *command = extractCommandOptions(argc, argv);
    
    pid_t id;
    int status;
    if ((id = fork()) < 0) {
        puts("Erro na criação do novo processo");
        exit(-2);
    } else if (id == 0) {
        serverRun(command);
        system(testes);
        exit(0);
    } else {
        wait(&status);
        statisticsPrint(command );
    }

    //signal(SIGUSR1, sigHandler);
    return 0;
}
