#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

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

    //first bind
    int bd=bind(sockfd,(struct sockaddr *)&server,sizeof(server));
    if(bd==-1){
        printf("\nBind Unsuccessful\n");
        exit(0);
    }else{
        printf("\nBind Successful\n");
    }

    //now receive the roll num from the client
    int rollnum;
    struct sockaddr_in client;
    socklen_t len=sizeof(client);
    int r=recvfrom(sockfd,&rollnum,sizeof(rollnum),0,(struct sockaddr *)&client,&len);
    if(r==-1){
        printf("\nReceive unsuccessful\n");
        exit(0);
    }

    printf("\nRoll Number is : %d",rollnum);

    //Server will send the full name to the client
    char name[50];
    printf("\nEnter your full name : ");
    fgets(name, sizeof(name), stdin);

    int s = sendto(sockfd,(char *)name,strlen(name),0,(struct sockaddr *)&client,sizeof(client));
    
    if(s==-1){
        printf("\nMessage send unsucessful\n");
        exit(0);
    }else{
        printf("Message sent successfully\n");
    }
    close(sockfd);
    return 0;
}