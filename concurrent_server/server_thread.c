#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   //#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#define serv_port 6666
#define MAXSIZE 100
struct s_info{
	int connectfd;
};

void* echo(void* arg){
	struct s_info* ts = (struct s_info*)arg;
	while(1){		
		char buffer[MAXSIZE];
		printf("-----server waits to read-------\n");
		int n = read(ts->connectfd, buffer, sizeof(buffer)); //to block here 
		printf("%d\n", n);
		if(n==0||n==-1) break;                                  //ctrl+c -> break
		printf("-----server starts to write-----\n");
		write(ts->connectfd, buffer, n);
	}
	close(ts->connectfd);
}

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

	while(1){
		connectfd =  accept(listenfd, (struct sockaddr*)&clie_addr, &clie_addr_len);
		pthread_t tid;
		struct s_info ts;
		ts.connectfd = connectfd;
		pthread_create(&tid, NULL, echo, (void*)&ts);
	}
	close(listenfd);

	return 0;
}                                                                                     
