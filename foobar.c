#include <stdio.h>

const char* bar();
int foo();
int main()
{
	const char* v = bar();
	int n = foo();

	fprintf(stderr, "foo = %d bar = %s\n", n, v);
	return 0;
}
