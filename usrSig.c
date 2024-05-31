#include "usrSig.h"
#include "statsInfo.h"

int server_running  = 1;
extern int server_sockfd;
extern StatsInfo stats;

void handle_signal(int signal) {
    if (signal == SIGINT || signal == SIGTERM || signal == SIGUSR1) {
        server_running = 0;
        close(server_sockfd);
        FILE *arquivoStats = fopen(stats.statsFileName, "w+");

        fprintf(arquivoStats, "HTML: %d\nIMAGEM: %d\nTEXTO: %d\n", stats.html_count, stats.image_count, stats.text_count);
        fclose(arquivoStats);

        printf("[SERVER] - Shutting down server...\n");
    }
}
