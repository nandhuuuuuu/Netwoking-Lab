#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    char buf[100];
    char response[100];
    struct sockaddr_in server; 
    socklen_t server_len = sizeof(server);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);  

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    printf("Enter message to be sent: ");
    fgets(buf, 100, stdin); 
    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&server, server_len);

    recvfrom(sockfd, response, sizeof(response), 0, (struct sockaddr *)&server, &server_len);
    printf("Response from server: %s", response);

    close(sockfd);
    return 0;
}
