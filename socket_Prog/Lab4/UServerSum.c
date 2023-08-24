//Client send 10 float numbers to server. Server calculates the sum and sends the sum back to the client

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>


int main(int argc,char * argv[]){
    struct sockaddr_in server;
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);

    if(sockfd==-1){
        printf("\nSocket creating unsuccessful\n");
        exit(0);
    }else{
        printf("\nSocket creation successful\n");
    }

    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(argv[1]));
    server.sin_addr.s_addr=inet_addr(argv[2]);

    int b=bind(sockfd,(struct sockaddr *)&server,sizeof(server));
    if(b==-1){
        printf("\nBind unsuccessful\n");
        exit(0);
    }
    else{
        printf("\nBind Successful\n");
    }

    float buff[100];
    struct sockaddr_in client;
    socklen_t len=sizeof(client);

    int r=recvfrom(sockfd,(float *)buff,sizeof(buff),0,(struct sockaddr *)&client,&len);
    if(r==-1){
        printf("\nReceive unsuccessfull\n");
        exit(0);
    }
    buff[r]='\0';

    float sum=0.0;
    for(int i=0;i<10;i++){
        sum+=buff[i];
    }

    //Now i want to send this sum to the client
    socklen_t len1=sizeof(client);
    int s=sendto(sockfd,&sum,sizeof(sum),0,(struct sockaddr *)&client,len1);
    if(s==-1){
        printf("\nSend unsuccessful\n");
        exit(0);
    }else{
        printf("\nMessage sent successfully\n");
    }
    close(sockfd);
    return 0;
}