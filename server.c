//simply tcp server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   //#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#define serv_port 6666
#define MAXSIZE 100

int main()
{
	int listenfd;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port =  htons(serv_port);
	server_addr.sin_addr.s_addr =  htonl(INADDR_ANY);
	bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); 

	listen(listenfd, 5);

	int connectfd;
	struct sockaddr_in clie_addr;
	socklen_t clie_addr_len = sizeof(clie_addr);
   	connectfd =  accept(listenfd, (struct sockaddr*)&clie_addr, &clie_addr_len);

	while(1){
		char buffer[MAXSIZE];
		printf("-----server waits to read-------\n");
		int n = read(connectfd, buffer, sizeof(buffer)); //to block here 
		printf("-----server starts to write-----\n");
		sleep(5);
		write(connectfd, buffer, n);
	}
	close(listenfd);
	close(connectfd);

	return 0;
}                                                                                     
