#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in server, client;
    socklen_t client_len;
    char filename[1024];
    char response[1024];
    FILE *file;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Error binding socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);
    printf("File server is running, PID: %d\n", getpid());

    while (1) {
        client_len = sizeof(client);
        
        newsockfd = accept(sockfd, (struct sockaddr *)&client, &client_len);
        if (newsockfd < 0) {
            perror("Error accepting connection");
            continue;
        }

        memset(filename, 0, 1024);
        recv(newsockfd, filename, 1024, 0);
        printf("Client requested file: %s\n", filename);

        file = fopen(filename, "r");
        if (file) {
            memset(response, 0, 1024);
            fread(response, sizeof(char), 1024 - 1, file);
            fclose(file);
            send(newsockfd, response, strlen(response), 0);
        } else {
            snprintf(response, sizeof(response), "File '%.980s' not found. PID: %d", filename, getpid());
            send(newsockfd, response, strlen(response), 0);
        }

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}
