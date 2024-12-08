#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define WINDOW_SIZE 4

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    int base = 0;
    int next_seq_num = 0;
    int ack, nack;
    bool nack_received = false;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);

    while (base < MAX_FRAMES) {
        if (!nack_received) {
            while (next_seq_num < base + WINDOW_SIZE && next_seq_num < MAX_FRAMES) {
                printf("Sending frame %d\n", next_seq_num);
                if (sendto(sockfd, &next_seq_num, sizeof(next_seq_num), 0,
                           (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                    perror("Send failed");
                }
                next_seq_num++;
            }
        } else {
            printf("Resending frame %d due to NACK\n", nack);
            if (sendto(sockfd, &nack, sizeof(nack), 0,
                       (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                perror("Resend failed");
            }
            nack_received = false;
        }
        socklen_t len = sizeof(server_addr);
        if (recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&server_addr, &len) < 0) {
            perror("Receive failed");
        } else {
            printf("Received %s for frame %d\n", (ack >= base ? "ACK" : "NACK"), ack);
            if (ack >= base) {
                base = ack + 1;
            } else {
                nack = ack;
                nack_received = true;
            }
        }
        sleep(1);
    }
    close(sockfd);
    return 0;
}