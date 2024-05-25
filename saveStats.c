#include "statsInfo.h"


void *statisticsPrint(StatsInfo stats){
    FILE *arquivoStats = fopen(stats.statsFileName, "w+");
    if (arquivoStats != NULL) {
        fprintf(arquivoStats, "HTML: %d\nIMAGEM: %d\nTEXTO: %d\n", stats.html_count, stats.image_count, stats.text_count);
        fclose(arquivoStats);
    } else {
        fprintf(stderr,"[SERVER] - Failed to open stats.txt\n");
    }

    return NULL;
}


