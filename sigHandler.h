#ifndef USER_SIG_H
#define USER_SIG_H

typedef struct {
    int html_count;
    int image_count;
    int text_count;
    char *statsFileName;
} StatsInfo;

extern StatsInfo stats;

void sigHandler(int signal);

#endif
