#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<time.h>

int main() {
    char buf[100];
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    while(1){
        recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client, &client_len);
        printf("Message from client: %s", buf);

        time_t current_time = time(NULL);
        char *time_str = ctime(&current_time);
        sendto(sockfd, time_str, strlen(time_str), 0, (struct sockaddr *)&client, client_len);
    }

    close(sockfd);
    return 0;
}
