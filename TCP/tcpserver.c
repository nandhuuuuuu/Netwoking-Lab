#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>     

int main(){
    char buf[100];
    struct sockaddr_in server,client;
    socklen_t server_len,client_len;
    int sockfd,newsockfd;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    server_len = sizeof(server);
    client_len = sizeof(client);

    bind(sockfd,(struct sockaddr *)&server,server_len);
    listen(sockfd,5);
    newsockfd = accept(sockfd,(struct sockaddr *)&client,&client_len);
    recv(newsockfd,buf,sizeof(buf),0);
    printf("Message from client: %s",buf);

    close(newsockfd);
    close(sockfd);
    return 0;
}