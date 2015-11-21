#include <stdio.h>

int main(void)
{
	volatile int v;
	volatile int *doc = NULL;
	volatile int getCount = 1;
	int errorCount;
	volatile int res = 0;
	volatile int res2 = 0;
	volatile int res3 = 0;
	volatile int res4 = 1;
	if (doc == NULL & (errorCount = getCount) > 0) {
		fprintf(stderr, "All true\n");
	} else {
		fprintf(stderr, "not All true\n");
	}
	if ((doc == NULL) && ((errorCount = getCount) > 0)) {
		fprintf(stderr, "All true\n");
	} else {
		fprintf(stderr, "not All true\n");
	}

	if ((1 == res) &&
		(1 == res2) ||
		(1 == res3) ||
		(1 == res4))
	{
		fprintf(stderr, "res == 1 and one of res2, res3 or res4 is == 1 too \n");
	}
}
