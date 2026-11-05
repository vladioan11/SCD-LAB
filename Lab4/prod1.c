#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define BUF_SIZE 8192
const int offset1 = 0x64
const int offset2 = 0xC8

int main(int argc, char *argv[])
{
	int fd;
	char *shmp;
	char usage[256];
	if((argc!=2) || (argv[1][0] !='/')) {
		sprintf(usage, "Utlizare: %s /nume_shm\n", argv[0]);
		fprintf(stderr, "%s", usage);
		exit(EXIT_FAILURE);
	}
	
}
