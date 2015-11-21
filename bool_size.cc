#include <stdio.h>

int main(void)
{
	bool b = true;
	int v = 12;
	//b = !b;
	fprintf(stderr, "v = %d, v+b = %d\n", v, v+b);
	return 0;
}
