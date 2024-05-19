#include "main.h"

int main(int argc, char *argv[]) {
    Command *command = parse(argc, argv);
    start_server(command);
    return 0;
}
