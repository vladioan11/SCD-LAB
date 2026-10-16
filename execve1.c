#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
	if (argc < 2){
		fprintf(stderr, "Utilizare: %s [optiuni ls]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	argv[0]="ls";
	execve("/bin/ls", argv, envp);
	fprintf(stderr, "Eroare la execve: %s\n", strerror(errno));
	exit(EXIT_FAILURE);
}
