#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_SEQ 4         
#define TOTAL_FRAMES 10    
#define TIMEOUT 2     

int main() {
    struct sockaddr_in server;
    int base = 0, next_seq_num = 0;
    int ack_num;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (base < TOTAL_FRAMES) {
        while (next_seq_num < base + MAX_SEQ && next_seq_num < TOTAL_FRAMES) {
            sendto(sockfd, &next_seq_num, sizeof(next_seq_num), 0, (struct sockaddr*)&server, sizeof(server));
            printf("Sent frame: %d\n", next_seq_num);
            next_seq_num++;
            sleep(1); 
        }

        int timeout_counter = 0;
        while (timeout_counter < TIMEOUT) {
            if (recv(sockfd, &ack_num, sizeof(ack_num), MSG_DONTWAIT) > 0) {
                printf("Received ACK: %d\n", ack_num);
                if (ack_num >= base) {
                    base = ack_num + 1;  
                }
                break; 
            }
            timeout_counter++;
            sleep(1); 
        }

        if (timeout_counter == TIMEOUT) {
            printf("Timeout! Resending frames starting from %d\n", base);
            for (int i = base; i < next_seq_num; i++) {
                sendto(sockfd, &i, sizeof(i), 0, (struct sockaddr*)&server, sizeof(server));
                printf("Resent frame: %d\n", i);
            }
        }
    }

    close(sockfd);
    return 0;
}
