#include "usrSig.h"
#include "statsInfo.h"

extern int server_running;
extern int server_sockfd;
extern StatsInfo stats;
extern FILE *logfile;

void handle_signal(int signal) {
    if (signal == SIGINT || signal == SIGTERM || signal == SIGUSR1) {
        server_running = 0;
        
        FILE *arquivoStats = fopen(stats.statsFileName, "w+");

        fprintf(arquivoStats, "HTML: %d\nIMAGEM: %d\nTEXTO: %d\n", stats.html_count, stats.image_count, stats.text_count);
        fclose(arquivoStats);
        fclose(logfile);
        close(server_sockfd);
        printf("[SERVER] - Shutting down server...\n");
    }
}
