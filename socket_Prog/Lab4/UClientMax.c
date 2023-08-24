//Clinet send two integer number to the server, server send the max among two to client

#include<stdio.h>
#include<stdlib.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
int main(int argc,char * argv[]){
    struct sockaddr_in server;
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1){
        printf("\nSocket creation unsuccessful\n");
        exit(0);
    }else{
        printf("\nSocket creation successful\n");
    }

    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(argv[1]));
    server.sin_addr.s_addr=inet_addr(argv[2]);

    int buff[50];
    
    for(int i=0;i<2;i++){
        printf("\nEnter the %d number:",i+1);
        scanf("%d",&buff[i]);
    }

    int s=sendto(sockfd,(int *)buff,sizeof(buff),0,(const struct sockaddr *)&server,sizeof(server));
    if(s==-1){
        printf("\nMessage send unsuccessfull\n");
        exit(0);
    }else{
        printf("\nMessage send successful\n");
    }

    //receiving the message from the server
    char msg[1000];
    struct sockaddr_in client;
    socklen_t len1=sizeof(client);
    int r=recvfrom(sockfd,(char *)msg,1000,0,(struct sockaddr *)&client,&len1);
    if(r==-1){
        printf("\nReceive Unsuccessful\n");
        exit(0);
    }
    msg[r]='\0';
    printf("\n%s\n",msg);
    close(sockfd);
    return 0;
}