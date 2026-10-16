#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main( int argc, char *argv[])
{
	pid_t newpid;
	int num_children =4;
	int flags;

	flags = fcntl(1, F_GETFL);
	flags |= O_APPEND;
	if(fcntl(STDOUT_FILENO, F_SETFL, flags) == -1)
		exit(1);
	if(!isatty(fileno(stdout)))
		fflush(stdout);

	while(num_children--> 0){
		newpid = fork();
		if(newpid==0)
			break;
	}
	printf("Process ID=%d\n", getpid());
	return 0;
}
