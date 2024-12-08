#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server;
    char filename[1024];
    char response[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Error connecting to server");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Enter the filename to request: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; 

    send(sockfd, filename, strlen(filename), 0);

    memset(response, 0, 1024);
    recv(sockfd, response, sizeof(filename), 0);
    printf("Response from server:\n%s\n", response);

    close(sockfd);
    return 0;
}
