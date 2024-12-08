#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

int main(){
    char buf[100];
    struct sockaddr_in server, client;
    socklen_t client_len;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    client_len = sizeof(client);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client, &client_len);
    printf("Message from client: %s", buf);
 
    close(sockfd);
    return 0;
}