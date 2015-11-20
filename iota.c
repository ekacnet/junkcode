#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char buf[16];

	int i = -12;

	itoa(i, buf, 10);
	fprintf(stderr, "buf=%s\n", buf);
	return 0;
}
