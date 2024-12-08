#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFER_SIZE 100
#define PORT 8080
#define IP_ADDRESS "127.0.0.1"

int main() {
    int sockfd;
    struct sockaddr_in server; 
    char buffer[BUFFER_SIZE];
    int noframes, i = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    printf("Enter the number of frames: ");
    scanf("%d", &noframes);

    while (noframes > 0) {
        snprintf(buffer, BUFFER_SIZE, "Frame %d", i);

        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, sizeof(server)) < 0) {
            perror("Error sending frame");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        printf("Sent frame %d\n", i);

        memset(buffer, 0, BUFFER_SIZE);

        int k = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (k < 0) {
            perror("Error receiving acknowledgment");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        buffer[k] = '\0'; 
        printf("Ack received: %s\n", buffer);

        noframes--;
        i++;

        sleep(1);  
    }

    printf("End of Stop-and-Wait protocol\n");
    close(sockfd);
    return 0;
}
