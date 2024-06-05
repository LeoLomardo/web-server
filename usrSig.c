#include "usrSig.h"

extern int runningFlag;
extern int server_sockfd;

extern StatsInfo stats;
extern FILE *logFile;
extern LogBuffer log_buffer;

void sigHndler(int signal){
    if(signal == SIGINT || signal == SIGTERM || signal == SIGUSR1){
        runningFlag = 0;
        
        FILE *arquivoStats = fopen(stats.statsFileName, "w+");

        fprintf(arquivoStats, "HTML: %d\nIMAGEM: %d\nTEXTO: %d\n", stats.html_count, stats.image_count, stats.text_count);
        fclose(arquivoStats);
        
        fclose(logFile);
        free(stats.statsFileName);
        close(server_sockfd);
        printf("sigHndler - Server off\n");
    }
}
