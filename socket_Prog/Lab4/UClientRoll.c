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

    //client will send roll number to server
    int rollnum;
    printf("\nEnter your roll Number : ");
    scanf("%d",&rollnum);
    int s=sendto(sockfd,&rollnum,sizeof(rollnum),0,(struct sockaddr *)&server,sizeof(server));
    if(s==-1){
        printf("\nMessage send unsuccessful\n");
        exit(0);
    }else{
        printf("\nMessage sent successfully\n");
    }

    //client will receive the name from the server
    char name[50];
    socklen_t len1=sizeof(server);
    int r=recvfrom(sockfd,(char *)name,sizeof(name),0,(struct sockaddr *)&server,&len1);
    if(r==-1){
        printf("\nReceive Unsuccessful\n");
        exit(0);
    }
    name[r]='\0';
    printf("Full name is : %s",name);
    close(sockfd);
    return 0;
}