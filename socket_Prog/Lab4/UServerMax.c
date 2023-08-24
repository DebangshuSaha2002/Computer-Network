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

    int bd=bind(sockfd,(struct sockaddr *)&server,sizeof(server));
    if(bd==-1){
        printf("\nBind unsuccessful\n");
        exit(0);
    }else{
        printf("\nBind Successful\n");
    }

    struct sockaddr_in client;
    int buff[100];
    socklen_t len=sizeof(client);
    int r=recvfrom(sockfd,(int *)buff,sizeof(buff),0,(struct sockaddr *)&client,&len);
    if(r==-1){
        printf("\nMessage receive unsuccessful\n");
        exit(0);
    }
    buff[r]='\0';
    int num1=buff[0];
    int num2=buff[1];
    printf("\nNumber 1 is %d",num1);
    printf("\nNumber 2 is %d",num2);
    
    char msg[1000];
    if(num1>num2){
        sprintf(msg,"%d is greater than %d",num1,num2);
    }
    else{
        sprintf(msg,"%d is greater than %d",num2,num1);
    }
    
    //Sending the msg[] to client
    int s=sendto(sockfd,(char *)msg,strlen(msg),0,(const struct sockaddr *)&client,sizeof(client));
    if(s==-1){
        printf("\nSend Unsuccessful\n");
        exit(0);
    }else{
        printf("\nSend Successful\n");
    }

    close(sockfd);
    return 0;

}