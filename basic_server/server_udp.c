#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   //#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define serv_port 6666
#define MAXSIZE 100

int main()
{
	int serverfd;
	serverfd = socket(AF_INET, SOCK_DGRAM, 0);

  	struct	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port =  htons(serv_port);
	server_addr.sin_addr.s_addr =  htonl(INADDR_ANY);
	bind(serverfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); 

	
	struct sockaddr_in clie_addr;
	socklen_t clie_addr_len = sizeof(clie_addr);
	while(1){
		char buffer[MAXSIZE];
		printf("-----server waits to read-------\n");
		//read -> recvfrom
		int n = recvfrom(serverfd, buffer, MAXSIZE, 0, (struct sockaddr*)&clie_addr, &clie_addr_len);  
		printf("%d\n", n);
		if(n==0) break;                                  
		printf("-----server starts to write-----\n");
		//write -> sendto
		sendto(serverfd, buffer, n, 0, (struct sockaddr*)&clie_addr, clie_addr_len);
	}
	close(serverfd);

	return 0;
}                                                                                     
