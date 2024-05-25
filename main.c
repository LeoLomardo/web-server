#include "main.h"


// int html_count = 0;
// int image_count = 0;
// int text_count = 0;

int main(int argc, char *argv[]) {

    Command *command = extractCommandOptions(argc, argv);
    serverRun(command);
    
    return 0;
}
