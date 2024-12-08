#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);
    int received_frame, ack_num;
    int expected_seq_num = 0;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
   
    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    while (1) {
        recvfrom(sockfd, &received_frame, sizeof(received_frame), 0, (struct sockaddr*)&client, &client_len);
        printf("Received frame: %d\n", received_frame);

        ack_num = (received_frame == expected_seq_num) ? expected_seq_num : expected_seq_num - 1;
        if (received_frame == expected_seq_num) {
            expected_seq_num++;
        }

        sendto(sockfd, &ack_num, sizeof(ack_num), 0, (struct sockaddr*)&client, client_len);
        printf("Sent ACK for frame %d\n", ack_num);
    }

    close(sockfd);
    return 0;
}
