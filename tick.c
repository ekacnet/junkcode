#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	char* pipe;
	int fd;

	if (argc != 2) {
		exit(1);
	}
	pipe =argv[1];
	fd = open(pipe, O_RDWR);

	if (fd < 0) {
		exit(2);
	}

	write(fd, "tick", 4);
	close(fd);
	return 0;
}
