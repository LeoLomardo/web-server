#include <stdio.h>
#include "client.h"

extern LogBuffer log_buffer;
extern Command *command;
extern StatsInfo stats;

void *clientRequest(void *client_sockfd) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    int sock = *(int *)client_sockfd;
    free(client_sockfd);
    
    char buffer[MAX_BUFFER_SIZE];
    

    int read_size = read(sock, buffer, MAX_BUFFER_SIZE-1);
    if (read_size > 0) {
        buffer[read_size] = '\0';
        printf(" %s\n", buffer);
    } else {
        fprintf(stderr, "[SERVER] - Read failed\n");
        //close(sock);
    }

    char method[10], path[255], protocol[10];
    sscanf(buffer, "%s %s %s", method, path, protocol);
    
    char full_path[256] = ".";
    strncat(full_path, path, sizeof(full_path) - strlen(full_path) - 1);

    /**
     * Verificar melhor maneira de ler o arquivo, rb/rb+ ou r/r+
     * 
     */
    FILE *inputFile = fopen(full_path, "r");
    if (inputFile == NULL){

        const char *error_message = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n";
        write(sock, error_message, strlen(error_message));
        snprintf(buffer, 1024, "%04d-%02d-%02d %02d:%02d:%02d 404 Not Found: %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, full_path);
        LEntry(&log_buffer, buffer);

    }else{
        char *ext = strrchr(full_path, '.');
        char *header;
        char content_type[50] ;

        struct stat lastChange;
        if (stat(full_path, &lastChange) == -1) {
            fprintf(stderr, "deu merda aqui e nao tenho mais neuronios pra descobrir a quem essa mensagem de erro se refere\n");
            fclose(inputFile);
            close(sock);
            //free(buffer);
            return NULL;
        }
        stat(full_path, &lastChange);
        
        int content_length = lastChange.st_size;
        char etag[64];
        snprintf(etag, sizeof(etag), "W/\"%lx-%lx\"", lastChange.st_size, lastChange.st_mtime);

        if (ext != NULL){
            if (strcmp(ext, ".html") == 0) {
                stats.html_count++;
                snprintf(content_type, sizeof(content_type), "text/html; charset=UTF-8");
            } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
                stats.image_count++;
                snprintf(content_type, sizeof(content_type), "image/jpeg");
            } else if (strcmp(ext, ".png") == 0) {
                stats.image_count++;
                snprintf(content_type, sizeof(content_type), "image/png");
            } else {
                stats.text_count++;
                snprintf(content_type, sizeof(content_type), "text/plain; charset=UTF-8");
            }
        }else{
            strncpy(content_type, "unknown", sizeof(content_type) - 1);
        }
        header = (char*)malloc(1024 * sizeof(char));
        if (header == NULL) {
            fprintf(stderr, "[SERVER] - Error allocating memory for header\n");
            fclose(inputFile);
            close(sock);
            //free(buffer);
            return NULL;
        }
        snprintf(header, 1024,"HTTP/1.1 200 OK\r\n"
                              "Server: FerramentasUnixPUC/1.1\r\n"
                              "ETag: %s\r\n"
                              "Last-Modified: %s\r"
                              "Content-Type: %s\r\n"
                              "Content-Length: %d\r\n"
                              "Date: %s\r\n\r\n",
                              etag, ctime(&lastChange.st_mtime), content_type, content_length, asctime(t));

        write(sock, header, strlen(header));
        printf(" %s\n", header);
        free(header);

        

        int bytes_read;
        while ((bytes_read = fread(buffer, 1, MAX_BUFFER_SIZE, inputFile)) > 0) {
            write(sock, buffer, bytes_read);
            printf("%s\n", buffer);
        }

        snprintf(buffer, MAX_BUFFER_SIZE, "%04d-%02d-%02d %02d:%02d:%02d 200 OK: %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, full_path);
        LEntry(&log_buffer, buffer);
        fclose(inputFile);
        
        
    }
    //pthread_mutex_lock(&stats.stats_mutex);
    //statisticsPrint(stats);
    //pthread_mutex_unlock(&stats.stats_mutex);

    close(sock);

    return NULL;
}
