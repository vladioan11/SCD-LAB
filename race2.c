#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

volatile sig_atomic_t done =0;
void usr_handler(int sig){
	if (sig==SIGUSR2)
		done=1;
}
void produce_data(int fd)
{
	char data[]="abcdefghijklmnoprst:";
	pid_t ppid;
	struct sigaction act;
	int pos=0;
	int count =0;
	act.sa_flags =0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = usr_handler;
	sigaction(SIGUSR1, &act, NULL);
	ppid = getppid();

	while (!done){
		printf("\n[c]opilul scrie in fisier...\n");
		usleep(random()%400000);
		lseek(fd, pos, SEEK_SET);
		if(write(fd, data, strlen(data))==-1)
		{
			perror("Eroare la scriere");
			exit(EXIT_FAILURE);
		}
		pos = lseek(fd, 0, SEEK_END);
		if(++count<20){
			kill(ppid, SIGUSR1);
			pause();
		} else{
			kill(ppid, SIGUSR2);
			done=1;
		}
	}
	exit(EXIT_SUCCESS);
	
}

int main(int argc, char *argv[])
{
	pid_t pid;
	const int CHUNKSIZE = 8;
	struct sigaction sigact;
	int fd;
	char buffer[CHUNKSIZE+1];
	int pos=0;
	size_t bytes_read;
	if (argc<2){
		fprintf(stderr, "Utilizare: %s nume_fisier\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	srandom(time(NULL));
	fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1){
		perror("Eroare la deschidere fisier");
		exit(EXIT_FAILURE);
	}
	 pid = fork();
	 if(pid==-1){
	 	perror("Eroare la fork");
	 	exit(EXIT_FAILURE);
	 } else if (pid==0){
	 	produce_data(fd);
	 } else{
	 	sigact.sa_flags =0;
	 	sigemptyset(&sigact.sa_mask);
	 	sigact.sa_handler = usr_handler;
	 	if(sigaction(SIGUSR1, &sigact, NULL)==-1){
	 		perror("Eroare la sigaction");
	 		exit(EXIT_FAILURE);
	 	}
	 	if(sigaction(SIGUSR2, &sigact, NULL)==-1){
	 		perror("Eroare la sigaction");
	 		exit(EXIT_FAILURE);
	 		
	 	}
	 	while(1){
	 		pause();
	 		int unread_bytes=lseek(fd, 0, SEEK_END) - pos;
	 		lseek(fd, pos, SEEK_SET);
	 		while(unread_bytes>=CHUNKSIZE){
	 			bytes_read = read(fd, buffer, CHUNKSIZE);
	 			if(bytes_read == (size_t)-1){
	 				perror("Eroare la citire");
	 				exit(EXIT_FAILURE);
	 			}
	 			if (bytes_read!=CHUNKSIZE){
	 				fprintf(stderr, "Citire incompleta\n");
	 				exit(EXIT_FAILURE);
	 			}
	 			unread_bytes-=CHUNKSIZE;
	 			buffer[CHUNKSIZE]='\0';
	 			printf("[p]%s\n", buffer);
	 		}
	 		if(done){
	 			if(unread_bytes>0){
	 				bytes_read = read(fd, buffer, unread_bytes);
	 				if(bytes_read == (size_t)-1){
	 					perror("Eroare la citire");
	 					exit(EXIT_FAILURE);
	 				}
	 				buffer[unread_bytes]='\0';
	 				printf("[p]%s\n", buffer);
	 			}
	 			close(fd);
	 			exit(EXIT_SUCCESS);
	 		} else{
	 			pos = lseek(fd, 0, SEEK_CUR);
	 			kill(pid, SIGUSR1);
	 		}
	 	}
	 }
	 return 0;
}
