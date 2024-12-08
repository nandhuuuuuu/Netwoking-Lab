#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_FRAMES 10
#define PORT 8080

int main() {
    struct sockaddr_in server_addr, client_addr;
    int frame, expected_frame = 0;
    socklen_t len = sizeof(client_addr);
    int ack, nack;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Server is Awake\n");
    while (expected_frame < MAX_FRAMES) {
        if (recvfrom(sockfd, &frame, sizeof(frame), 0, (struct sockaddr*)&client_addr, &len) < 0) {
            perror("Receive failed");
            continue; 
        }
        printf("Received frame %d\n", frame);
        if (frame == expected_frame) {
            ack = expected_frame;
            expected_frame++;
            printf("Sending ACK for frame %d\n", ack);
            sendto(sockfd, &ack, sizeof(ack), 0, (const struct sockaddr*)&client_addr, len);
        } 
        else if (frame > expected_frame) {
            nack = expected_frame;  
            printf("Sending NACK for frame %d (expected %d)\n", frame, nack);
            sendto(sockfd, &nack, sizeof(nack), 0, (const struct sockaddr*)&client_addr, len);
        }
        else if (frame < expected_frame) {
            ack = frame;
            printf("Sending duplicate ACK for frame %d\n", ack);
            sendto(sockfd, &ack, sizeof(ack), 0, (const struct sockaddr*)&client_addr, len);
        }
    }
    printf("All frames received. Closing server.\n");
    close(sockfd);
    return 0;
}


