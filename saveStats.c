#include "statsInfo.h"

void *statisticsPrint(StatsInfo stats){

    FILE *arquivoStats = fopen(stats.statsFileName, "w+");

    fprintf(arquivoStats, "HTML: %d\nIMAGEM: %d\nTEXTO: %d\n", stats.html_count, stats.image_count, stats.text_count);
    fclose(arquivoStats);
    
    return NULL;
}


