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
	clientfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr)); //very important 
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	while(1){
		char message[MAXSIZE];
		printf("input a string: ");
		fgets(message, MAXSIZE, stdin);
		printf("-----client starts to write-----\n");
		sendto(clientfd, message, strlen(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
		printf("-----client waits to read-------\n");
		struct sockaddr_in client_addr;
		int client_addr_len = sizeof(client_addr);
		recvfrom(clientfd, message, MAXSIZE, 0, (struct sockaddr*)&client_addr, &client_addr_len);
		printf("%s\n", message);
	}
	close(clientfd);
	
	return 0;
}
