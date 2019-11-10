#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	pid_t pid;
	if((pid=fork())==0){
		printf("\nThis is a child process");
		printf(" whose PID is %d", getpid());
		printf(", GPID is %d", getpgid(0));
		printf(", SID is %d\n", getsid(0));
		setsid();
		printf("-----------------------------changed-----------------------------\n");
		printf("This is a changed child process");
		printf(" whose PID is %d", getpid());
		printf(", GPID is %d", getpgid(0));
		printf(", SID is %d\n", getsid(0));
	}
	else{
		printf("This is a parent process");
		printf(" whose PID is %d", getpid());
		printf(", GPID is %d", getpgid(0));
		printf(", SID is %d\n", getsid(0));
		//sleep(15);
		exit(0);
	}

	while(1);
}
