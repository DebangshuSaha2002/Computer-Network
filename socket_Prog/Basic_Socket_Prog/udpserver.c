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
	
	int bd=bind(sockfd,(struct sockaddr *)& server,sizeof(server));
	if(bd==-1){
		printf("Bind Error\n");
		exit(0);
	}
	else{
		printf("\nBind successfull\n");
	}
	struct sockaddr_in client;
	while (1) {
        char buff[50];
        int len = sizeof(client);
        
        int r = recvfrom(sockfd, buff, sizeof(buff)-1, 0, (struct sockaddr *)&client, &len);
        if (r == -1) {
            perror("Receive error");
            close(sockfd);
            exit(1);
        }

        // buff[r] = '\0';
        printf("Received message: %s\n", buff);

        if (strncmp(buff, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        }
    }
	close(sockfd);
	return 0;
}
