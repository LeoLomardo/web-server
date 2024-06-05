#include "server.h"

LogBuffer log_buffer;
StatsInfo stats;

int runningFlag = 1;
int server_sockfd;

void serverRun(Command *command){
    if(command == NULL){
        fprintf(stderr, "serverRun - ERROR NULL options\n");
        exit(EXIT_FAILURE);
    }

    stats.html_count = 0;
    stats.image_count = 0;
    stats.text_count = 0;

    stats.statsFileName = (char *)malloc(strlen(command->statsFilename) + 1);
    if(stats.statsFileName == NULL){
        fprintf(stderr, "serverRun - ERROR failed to allocate memory for statsFileName\n");
        exit(EXIT_FAILURE);
    }
    strcpy(stats.statsFileName, command->statsFilename);
    free(command->statsFilename);

    signal(SIGUSR1, sigHndler);
    /**
     * Mantive o SIGINT apenas para agilizar os testes
     */
    signal(SIGINT, sigHndler);

    LBufferInit(&log_buffer, command->logFilename);
    free(command->logFilename);

    pthread_t log_thread;
    if(pthread_create(&log_thread, NULL, LPrinfFile, &log_buffer) != 0){
        fprintf(stderr, "serverRun - ERROR failed creating thread to write log entries\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&(server_addr.sin_zero), '\0', 8);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(command->port);
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(server_sockfd== -1){
        fprintf(stderr, "serverRun - Error creating socket\n");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    /*
     * @Note: Nessa parte do codigo, enquanto estava pesquisando sobre, vi que poderia declarar uma 
     * variavel int e passar o valor 1 para ela, e passar o endereco dessa variavel para o setsockopt, 
     * mas tambem vi que da pra utilizar dessa maneira, achei mais elegante. 
    */
    if(setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) == -1){
        fprintf(stderr, "serverRun - ERROR Failed to use port\n");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    if(bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1){
        fprintf(stderr, "serverRun - ERROR Bind failed\n");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    if(listen(server_sockfd, SOMAXCONN)== -1){
        fprintf(stderr, "serverRun - ERROR Listen failed\n");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    printf("serverRun - Server started on port %d rooted %s\n", command->port, command->rootDir);
    printf("serverRun - Para " RED"terminar " RESET "o servidor, use o comando:" YEL " kill -SIGUSR1 %d\n" RESET, getpid() );
    while(runningFlag){
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(server_sockfd, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int activity = select(server_sockfd + 1, &read_fds, NULL, NULL, &timeout);
        if(activity < 0 && errno != EINTR){
            fprintf(stderr, "serverRun - Select error\n");
            break;
        }

        if(activity > 0 && FD_ISSET(server_sockfd, &read_fds)){
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);

            int *new_sockfd = (int*)malloc(sizeof(int));
            if(new_sockfd == NULL){
                fprintf(stderr, "serverRun - ERROR failed to allocate memory for new socket\n");
            }

            *new_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_len);
            if(*new_sockfd < 0){
                fprintf(stderr, "serverRun - ERROR Accept\n");
                free(new_sockfd);
                continue;
            }

            printf("serverRun - New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            pthread_t thread_id;
            if(pthread_create(&thread_id, NULL, clientRequest, new_sockfd) != 0){
                fprintf(stderr, "serverRun - ERROR failed to create thread\n");
                free(new_sockfd);
                continue;
            }

            printf("serverRun - Thread created for client %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            pthread_detach(thread_id);
        }
    }
    pthread_cancel(log_thread);
    pthread_join(log_thread, NULL);
}
