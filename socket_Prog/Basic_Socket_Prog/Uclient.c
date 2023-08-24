#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc,char * argv[]){
    struct sockaddr_in server;
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1){
        printf("\nSocket Creation unsuccessful\n");
        exit(0);
    }else{
        printf("\nSocket Creation successful\n");
    }

    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(argv[1]));
    server.sin_addr.s_addr=inet_addr(argv[2]);

    char buff[50]="Debangshu saha";
    int s=sendto(sockfd,(char *)buff,strlen(buff),0,(const struct sockaddr *)&server,sizeof(server));
    if(s==-1){
        printf("\nMessage sent unsuccessfully\n");
        exit(0);
    }else{
        printf("\nMessage sent successfully\n");
    }
    close(sockfd);
    return 0;
}