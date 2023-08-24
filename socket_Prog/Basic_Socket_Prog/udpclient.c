#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
int main(int argc , char * argv[]){
	int sockfd;
	struct sockaddr_in server;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1){
		printf("Socket not created\n");
		exit(0);
	}
	else{
		printf("Socket created successfully\n");
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=inet_addr(argv[2]);
	
	char buff[50]="Hello World";
	int len=strlen(buff);
	int s=sendto(sockfd,(char *)buff,len,0,(const struct sockaddr *) & server,sizeof(server));
	if(s==-1){
		printf("Message send unsuccessful\n");
	}
	else{
		printf("Message sent successfully\n");
	}
	close(sockfd); 
	return 0;
}
