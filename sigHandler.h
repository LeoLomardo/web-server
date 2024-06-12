#ifndef USER_SIG_H
#define USER_SIG_H

typedef struct statsinfo{
    char *statsFileName;
    int html_count;
    int image_count;
    int text_count;
} StatsInfo;

extern StatsInfo stats;

void sigHandler(int signal);

#endif
