#include "client.h"

extern LogBuffer log_buffer;
extern Command *command;
extern StatsInfo stats;

void *clientRequest(void *client_sockfd){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    int sock = *(int *)client_sockfd;
    free(client_sockfd);
    
    char buffer[MAX_BUFFER_SIZE] ={0};
    
    int read_size = read(sock, buffer, MAX_BUFFER_SIZE-1);
    if(read_size > 0){
        buffer[read_size] = '\0';
        printf(" %s\n", buffer);
    }else{
        fprintf(stderr, "clientRequest - Failed to read buffer content\n");
        close(sock);
        return NULL;
    }

    char method[10] ={0}, path[255] ={0}, protocol[10] ={0};
    sscanf(buffer, "%s %s %s", method, path, protocol);
    
    char full_path[256] = ".";
    strncat(full_path, path, sizeof(full_path) - strlen(full_path) - 1);
    printf("clientRequest - Requested path: %s\n", full_path);

    FILE *inputFile = fopen(full_path, "rb");

    if(inputFile == NULL){
        const char *error_message = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n";
        write(sock, error_message, strlen(error_message));
        snprintf(buffer, MAX_BUFFER_SIZE, "%04d-%02d-%02d %02d:%02d:%02d 404 Not Found: %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, full_path);
        LEntry(&log_buffer, buffer);
        close(sock);
        return NULL;
    } 
    char *contentExtention = strrchr(full_path, '.');
    char header[MAX_BUFFER_SIZE] ={0};
    char content_type[80] ={0};

    struct stat lastChange;
    if(stat(full_path, &lastChange) == -1){
        fprintf(stderr, "clientRequest - Failed to get file input informations\n");
        fclose(inputFile);
        close(sock);
    }

    int content_length = lastChange.st_size;

    if(contentExtention != NULL){
        if(strcmp(contentExtention, ".html") == 0 || strcmp(contentExtention, ".htm") == 0){
            stats.html_count++;
            snprintf(content_type, sizeof(content_type), "text/html");
            /**
             * Utilizei SEEK_END para poder calcular o tamanho do arquivo e alocar a memoria necessaria 
             * Depois, para nao precisar utilizar rewind, utilizei SEEK_SET para voltar o ponteiro para o comeco do arquivo
             * Abaixo eu utilizo a variavel content_length para armazenar o tamanho do arquivo, porem quando eu utilizava ela dentro do if,
             * tinha problemas, entao preferi criar novamente utilizando essa maneira.
             */
            fseek(inputFile, 0, SEEK_END);
            long file_size = ftell(inputFile);
            fseek(inputFile, 0, SEEK_SET);
            
            char *file_content = malloc(file_size + 1);
            if(file_content){
                fread(file_content, 1, file_size, inputFile);
                file_content[file_size] = '\0';

                char *img_tag = file_content;
                char *txt_tag = file_content;

                while (img_tag || txt_tag){
                    if(img_tag){
                        img_tag = strstr(img_tag, "<img ");
                        if(img_tag){
                            stats.image_count++;
                            img_tag += 5;
                        }
                    }
                    if(txt_tag){
                        txt_tag = strstr(txt_tag, ".txt");
                        if(txt_tag){
                            stats.text_count++;
                            txt_tag += 4;
                        }
                    }
                }
                free(file_content);
            }
            rewind(inputFile); 
        }else if(strcmp(contentExtention, ".jpg") == 0 || strcmp(contentExtention, ".jpeg") == 0){
            stats.image_count++;
            snprintf(content_type, sizeof(content_type), "image/jpeg");
        }else if(strcmp(contentExtention, ".png") == 0){
            stats.image_count++;
            snprintf(content_type, sizeof(content_type), "image/png");
        }else{
            stats.text_count++;
            snprintf(content_type, sizeof(content_type), "text/plain");
        }
    }

    char timebuf[128];
    char lastmodbuf[128];
    strftime(timebuf, sizeof(timebuf), "%a, %d %b %Y %H:%M:%S GMT", gmtime(&now));
    strftime(lastmodbuf, sizeof(lastmodbuf), "%a, %d %b %Y %H:%M:%S GMT", gmtime(&lastChange.st_mtime));
    snprintf(header, sizeof(header), 
        "HTTP/1.1 200 OK\r\n"
        "Server:FerramentasUnixPUC/1.1\r\n"
        "Last-Modified:%s\r\n"
        "Content-Length:%d\r\n"
        "Date:%s\r\n"
        "Content-Type:%s\r\n\r\n", 
        lastmodbuf, content_length, timebuf, content_type);

    if(write(sock, header, strlen(header)) == -1){
        fprintf(stderr, "clientRequest - Failed to send header");
        fclose(inputFile);
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf(" %s\n", header);

    char ret_buffer[MAX_BUFFER_SIZE] = {0};

    int bytes_read;

    while ((bytes_read = fread(ret_buffer, 1, sizeof(ret_buffer), inputFile)) > 0){
       if(write(sock, ret_buffer, bytes_read) == -1){
            fprintf(stderr, "clientRequest - Failed to send file content\n");
            fclose(inputFile);
            close(sock);
            return NULL;
        }
    }
    /*
     * Nao consegui adicionar o tempo com o fuso brasileiro, e tambem tive um problema com o horario, quando faco mais de 1 requisicao, o log escreve horarios com
     * uma diferenca de tempo muito grande, e nao consegui resolver esse problema.
     */
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d 200 OK: %s\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, full_path);
    LEntry(&log_buffer, buffer);

    fclose(inputFile);
    close(sock);

    printf(" Para " RED"terminar " RESET "o servidor, use o comando:" YEL " kill -SIGUSR1 %d\n" RESET, getpid());
    return NULL;
}
