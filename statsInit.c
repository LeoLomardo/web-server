#include "statsInfo.h"

void initStats(StatsInfo stats, const char *filename) {
    stats.html_count = 0;
    stats.image_count = 0;
    stats.text_count = 0;

    stats.statsFileName = (char *)malloc(strlen(filename) + 1); 

    if (stats.statsFileName == NULL) {
        fprintf(stderr,"Failed to allocate memory for logFile\n");
        exit(EXIT_FAILURE);
    }
    strcpy(stats.statsFileName, filename);
    stats.statsFileName[sizeof(stats.statsFileName) - 1] = '\0';

}
