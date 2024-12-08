#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

int main(){
    char buf[100];
    struct sockaddr_in server;

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    connect(sockfd,(struct sockaddr *)&server,sizeof(server));
    printf("Enter data to be sent: ");
    fgets(buf,sizeof(buf),stdin);
    send(sockfd,buf,100,0);
  
    close(sockfd);
    return 0;
}