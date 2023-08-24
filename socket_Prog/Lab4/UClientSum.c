//Client send 10 float numbers to server. Server calculates the sum and sends the sum back to the client

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

    float buff[50];
    for(int i=0;i<10;i++){
        printf("\nEnter number %d ~ ",i+1);
        scanf("%f",&buff[i]);
    }

    int s=sendto(sockfd,(float *)buff,sizeof(buff),0,(struct sockaddr *)&server,sizeof(server));
    if(s==-1){
        printf("\nMessage send unsuccessful\n");
        exit(0);
    }else{
        printf("\nMessage sent successfully\n");
    }


    //Receive the sum ans from the server
    float sum;
    socklen_t l=sizeof(server);
    int r=recvfrom(sockfd,&sum,sizeof(sum),0,(struct sockaddr *)&server,&l);
    if(r==-1){
        printf("\nReceive Unsuccessful\n");
        exit(0);
    }
    printf("\nThe Sum is : %.2f",sum);
    close(sockfd);
    return 0;
}