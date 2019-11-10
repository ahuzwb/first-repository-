#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAXSIZE 100

int main(int argc, char* argv[])
{
	if(argc!=3){
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(1);
	}

	int clientfd;
	clientfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr)); //very important 
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	while(1){
		char message[MAXSIZE];
		printf("input a string: ");
		fgets(message, MAXSIZE, stdin);
		printf("-----client starts to write-----\n");
		write(clientfd, message, strlen(message));
		printf("-----client waits to read-------\n");
		read(clientfd, message, MAXSIZE);
		printf("%s\n", message);
	}
	close(clientfd);
	
	return 0;
}
