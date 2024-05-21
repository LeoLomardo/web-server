#ifndef SIGHANDLER_H
#define SIGHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void *statisticsPrint(const char *statsFile);

extern int html_count, image_count, text_count;

#endif