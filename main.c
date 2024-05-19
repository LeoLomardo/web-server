#include "main.h"

int main(int argc, char *argv[]) {
    Options *options = parse(argc, argv);
    start_server(options);
    return 0;
}
