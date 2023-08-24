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
    char msg[1000];

    while(1){
        printf("\nEnter your Message : ");
        fgets(msg,sizeof(msg),stdin);

        size_t msg_len = strlen(msg);
        if (msg_len > 0 && msg[msg_len - 1] == '\n') {
            msg[msg_len - 1] = '\0';
        }

        int s=sendto(sockfd,(char *)msg,sizeof(msg),0,(struct sockaddr *)&server,sizeof(server));
        if(s==-1){
            printf("\nMessage send unsuccessful\n");
            exit(0);
        }else{
            printf("\nMessage sent successfully\n");
        }

        if(strcmp("exit",msg)==0){
            printf("\nEXITING");
            break;
        }

        //client will receive the name from the server
        char name[1000];
        socklen_t len1=sizeof(server);
        int r=recvfrom(sockfd,(char *)name,sizeof(name),0,(struct sockaddr *)&server,&len1);
        if(r==-1){
            printf("\nReceive Unsuccessful\n");
            exit(0);
        }
        name[r]='\0';
        if(strcmp("exit",name)==0){
            printf("\nServer requested exit. Exiting...\n");
            break;
        }
        printf("\nServer Message : %s",name);
    }
    close(sockfd);
    return 0;
}