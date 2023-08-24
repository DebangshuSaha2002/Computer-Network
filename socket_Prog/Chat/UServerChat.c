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
    char msg[1000];
    struct sockaddr_in client;
    socklen_t len=sizeof(client);
    while(1){
        int r=recvfrom(sockfd,(char *)msg,sizeof(msg),0,(struct sockaddr *)&client,&len);
        if(r==-1){
            printf("\nReceive unsuccessful\n");
            exit(0);
        }

        printf("\nClient Message : %s",msg);

        if(strcmp("exit",msg)==0){
            printf("\nClient requested exit. Exiting...\n");
            break;
        }

        //Server will send the full name to the client
        char name[50];
        printf("\nEnter your Message : ");
        fgets(name, sizeof(name), stdin);
        size_t name_len = strlen(name);
        if (name_len > 0 && name[name_len - 1] == '\n') {
            name[name_len - 1] = '\0';
        }
        
        int s = sendto(sockfd,(char *)name,strlen(name),0,(struct sockaddr *)&client,sizeof(client));
        
        if(s==-1){
            printf("\nMessage send unsucessful\n");
            exit(0);
        }else{
            printf("\nMessage sent successfully\n");
        }

        if(strcmp("exit",name)==0){
            printf("\nEXITING");
            break;
        }
    }
    close(sockfd);
    return 0;
}