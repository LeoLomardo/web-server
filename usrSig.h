#ifndef USER_SIG_H
#define USER_SIG_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>  

void handle_signal(int signal);

#endif
