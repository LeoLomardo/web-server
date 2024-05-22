#include "server.h"

LogBuffer log_buffer;

void serverRun(Command *command) {
    if (command == NULL) {
        fprintf(stderr, "Options are NULL\n");
        exit(EXIT_FAILURE);
    }

    LBufferInit(&log_buffer, command->logFilename);

    pthread_t log_thread;
    if (pthread_create(&log_thread, NULL, LPrinfFile, &log_buffer) != 0) {
        perror("Failed to create log writer thread");
        exit(EXIT_FAILURE);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[CONSOLE] - Error creating socket\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(command->port);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("[CONSOLE] - Bind failed\n");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0) {
        perror("[CONSOLE] - Listen failed\n");
        exit(EXIT_FAILURE);
    }

    printf("[CONSOLE] - Server started on port %d rooted @%s\n\n", command->port, command->rootDir);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int *new_sockfd = malloc(sizeof(int));
        if (new_sockfd == NULL) {
            perror("[CONSOLE] - Failed to allocate memory for new socket\n");
            continue;
        }
        *new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
        if (*new_sockfd < 0) {
            perror("[CONSOLE] - Accept failed\n");
            free(new_sockfd);
            continue;
        }

        printf("[SERVER] - Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, clientRequest, new_sockfd) != 0) {
            perror("[CONSOLE] - Failed to create thread\n");
            close(*new_sockfd);
            free(new_sockfd);
            continue;
        }
        printf("[SERVER] - Created thread to handle client %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        pthread_detach(thread_id);
       

    }
}
