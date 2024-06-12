#include "sigHandler.h"
#include "clientRequest.h"
#include "log.h"
#include "serverRun.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>  
#include <signal.h>

StatsInfo stats;

void sigHandler(int signal){
    if(signal == SIGINT || signal == SIGTERM || signal == SIGUSR1){
        runningFlag = 0;
        
        FILE *arquivoStats = fopen(stats.statsFileName, "w+");

        fprintf(arquivoStats, "HTML: %d\nIMAGEM: %d\nTEXTO: %d\n", stats.html_count, stats.image_count, stats.text_count);
        fclose(arquivoStats);
        
        fclose(logFile); //variavel global que vem do log.h e e declarada no LPrintFile.c
        free(stats.statsFileName);
        close(server_sockfd);
        printf("sigHandler - Server off\n");
    }
}
