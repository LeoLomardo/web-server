#include "client.h"

extern LogBuffer log_buffer;
extern StatsInfo stats;

void *clientRequest(void *client_sockfd) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int sock = *(int *)client_sockfd;
    free(client_sockfd);

    char buffer[1024];
    int read_size = read(sock, buffer, sizeof(buffer) - 1);
    if (read_size > 0) {
        buffer[read_size] = '\0';
        printf("[SERVER] - Received data: %s\n", buffer);
    } else {
        fprintf(stderr, "[SERVER] - Read failed\n");
    }

    char method[10], path[255], protocol[10];
    sscanf(buffer, "%s %s %s", method, path, protocol);

    char full_path[256] = ".";
    strcat(full_path, path);

    FILE *inputFile = fopen(full_path, "r+");
    printf("\033[1;31mTo terminate the server press : CTRL + C\n\n\033[0m");
    if (inputFile == NULL) {
        char *error_message = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n";
        write(sock, error_message, strlen(error_message));
        snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d 404 Not Found: %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, full_path);
        LEntry(&log_buffer, buffer);
    } else {
        char *ext = strrchr(full_path, '.');
        char *header;

        if (ext != NULL) {
            if (strcmp(ext, ".html") == 0) {
                stats.html_count++;
                header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
            } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0 || strcmp(ext, ".png") == 0) {
                stats.image_count++;
                if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
                    header = "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n";
                } else {
                    header = "HTTP/1.1 200 OK\r\nContent-Type: image/png\r\n\r\n";
                }
            } else {
                stats.text_count++;
                header = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
            } 
        } else {
            header = "HTTP/1.1 200 OK\r\nContent-Type: UNKNOWN/plain\r\n\r\n";
        }   

        write(sock, header, strlen(header));
        printf("[SERVER] - %s", header);

        char file_buffer[1024];
        int bytes_read;
        while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), inputFile)) > 0) {
            write(sock, file_buffer, bytes_read);
            printf("%s\n", file_buffer);
        }

        snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d 200 OK: %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, full_path);
        LEntry(&log_buffer, buffer);
        fclose(inputFile);
        printf("\033[1;31mTo terminate the server press : CTRL + C\n\n\033[0m");
    }
    
    statisticsPrint(stats);
    close(sock);

    return NULL;
}
