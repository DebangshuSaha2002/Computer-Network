#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char *argv[]){
	int sockfd;
	struct sockaddr_in server;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1){
		printf("Socket error\n");
		exit(0);
	}
	else{
		printf("Socket successful\n");
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=inet_addr(argv[2]);

	int bd=bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	if(bd==-1){
		printf("\nBind unsuccessful\n");
		exit(0);
	}
	else{
		printf("\nBind successful\n");
	}

	char buff[100];
	struct sockaddr_in client;
	int len=sizeof(client);
	int r=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&client,&len);
	if(r==-1){
		printf("Reveive error\n");
		exit(1);
	}
	buff[r]='\0';
	printf("\nMessage:%s\n",buff);
	close(sockfd);
	return 0;
}	
