#include "server.h"

LogBuffer log_buffer;
StatsInfo stats;

extern int server_running ;
int server_sockfd;


void serverRun(Command *command) {

    if (command == NULL) {
        fprintf(stderr, "[ERROR] Options are NULL\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client_addr;
    socklen_t client_len;

    stats.html_count = 0;
    stats.image_count = 0;
    stats.text_count = 0;

    stats.statsFileName = (char *)malloc(strlen(command->statsFilename) + 1);
    if (stats.statsFileName == NULL) {
        fprintf(stderr, "Failed to allocate memory for statsFileName\n");
        exit(EXIT_FAILURE);
    }
    strcpy(stats.statsFileName, command->statsFilename);

    signal(SIGINT, handle_signal);

    LBufferInit(&log_buffer, command->logFilename);

    pthread_t log_thread;
    if (pthread_create(&log_thread, NULL, LPrinfFile, &log_buffer) != 0) {
        fprintf(stderr, "[ERROR] Failed to create log writer thread\n");
        exit(EXIT_FAILURE);
    }


    struct sockaddr_in server_addr;
    memset(&(server_addr.sin_zero), '\0', 8);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(command->port);

    /*
     * Socket parametros:

     * AF_INET - IPv4
     * SOCK_STREAM - TCP
     * 0 - Protocolo padrao para requisicao feita
    */

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int client_sockfd;

    if (server_sockfd== -1) {
        fprintf(stderr, "[CONSOLE] - Error creating socket\n");
        exit(EXIT_FAILURE);
    }


    int opt = 1;
    if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))== -1) {
        fprintf(stderr, "[CONSOLE] - setsockopt(SO_REUSEADDR) failed\n");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    if (bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))== -1) {
        fprintf(stderr, "[CONSOLE] - Bind failed\n");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_sockfd, BACKLOG)== -1) {
        fprintf(stderr, "[CONSOLE] - Listen failed\n");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    printf("[CONSOLE] - Server started on port %d rooted %s\n\n", command->port, command->rootDir);
    printf("[CONSOLE] - Para terminar o servidor, use o comando: kill -SIGUSR1 %d\n", getpid());

    while (server_running) {
        
        client_len = sizeof(struct sockaddr_in);

        if ( (client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_len))== -1) {
            fprintf(stderr, "[CONSOLE] - Accept failed\n");
            continue;
        }

        printf("[SERVER] - IP:%s Porta:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        
        int *new_sock = malloc(sizeof(int));
        *new_sock = client_sockfd;

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, clientRequest,(void *) new_sock) != 0) {
            fprintf(stderr, "[CONSOLE] - Failed to create thread\n");
            close(*new_sock);
            free(new_sock);
            continue;
        }

        printf("[SERVER] - Created thread to handle client %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        pthread_detach(thread_id);

    }
    pthread_cancel(log_thread);
    pthread_join(log_thread, NULL);
    //free(stats.statsFileName);
}
