#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
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
	
    while (1) {
        char buff[50];
        printf("Enter a message: ");
        fgets(buff, sizeof(buff), stdin);
        int len = strlen(buff);

        if (sendto(sockfd, buff, len, 0, (const struct sockaddr *)&server, sizeof(server)) == -1) {
            perror("Send error");
            close(sockfd);
            exit(1);
        }

        if (strncmp(buff, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        }
    }
	close(sockfd);
	return 0;
}
