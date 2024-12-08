#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFER_SIZE 100
#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Error in binding");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is waiting for frames...\n");

    while (1) {
        addr_size = sizeof(client);
        memset(buffer, 0, BUFFER_SIZE);
        int k = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &addr_size);
        if (k < 0) {
            perror("Error receiving data");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        buffer[k] = '\0'; 
        printf("Received: %s\n", buffer);

        int frame_number;
        sscanf(buffer, "Frame %d", &frame_number);

        snprintf(buffer, BUFFER_SIZE, "Ack for frame %d", frame_number);
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client, addr_size) < 0) {
            perror("Error sending acknowledgment");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        printf("Ack sent for frame %d\n", frame_number);
    }

    close(sockfd);
    return 0;
}
