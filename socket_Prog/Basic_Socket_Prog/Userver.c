//UDP SERVER

#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<unistd.h>

int main(int argc , char * argv[]){
    struct sockaddr_in server;
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1){
        printf("\nSocket creation unsuccessful\n");
        exit(0);
    }else{
        printf("\nSocket created successfully\n");
    }

    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(argv[1]));
    server.sin_addr.s_addr=inet_addr(argv[2]);

    //now do the bind
    int bd=bind(sockfd,(struct sockaddr *)&server,sizeof(server));
    if(bd==-1){
        printf("\nBind unsuccessful\n");
        exit(0);
    }else{
        printf("\nBind Successful\n");
    }

    char buff[100];
    struct sockaddr_in client;
    int length=sizeof(client);
    int r=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&client,&length);
    if(r==-1){
        printf("\nReceive unsuccessful\n");
        exit(1);
    }

    buff[r]='\0';
    printf("\nThe message is: %s\n",buff);
    close(sockfd);
    return 0;
}