#include <stdio.h>

#define pouet(truc) \
	typedef char type_##truc; \
	typedef struct  { type_##truc bidule;} type__##truc; \
	if (0) { type__##truc bidule; (void)bidule; }


int main(void)
{
	pouet(toto);
	fprintf(stderr, "hi\n");
	return 0;
}
