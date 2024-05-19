
#include "log.h"
#include "sigHandler.h"

extern LogBuffer log_buffer;

void *handle_client(void *client_sockfd) {
    int sock = *(int *)client_sockfd;
    free(client_sockfd);

    char buffer[1024];
    int read_size = read(sock, buffer, sizeof(buffer) - 1);
    if (read_size > 0) {
        buffer[read_size] = '\0';
        printf("[SERVER] - Received data: %s\n", buffer);
    } else {
        perror("[SERVER] - Read failed\n");
    }

    char method[10], path[255], protocol[10];
    sscanf(buffer, "%s %s %s", method, path, protocol);

    char full_path[256] = ".";
    strcat(full_path, path);

    FILE *f = fopen(full_path, "r");

    if (f == NULL) {
        char *error_message = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n";
        write(sock, error_message, strlen(error_message));
        snprintf(buffer, sizeof(buffer), "404 Not Found: %s\n", full_path);
        add_log_entry(&log_buffer, buffer);
    } else {
        char *header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        write(sock, header, strlen(header));
        printf("[SERVER] - %s", header);

        char file_buffer[1024];
        int bytes_read;
        while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), f)) > 0) {
            write(sock, file_buffer, bytes_read);
            printf("%s\n", file_buffer);
        }
        snprintf(buffer, sizeof(buffer), "200 OK: %s\n", full_path);
        add_log_entry(&log_buffer, buffer);
        log_request(&log_buffer, full_path);
        fclose(f);
    }

    close(sock);

    return NULL;
}
