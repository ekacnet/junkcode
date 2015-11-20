#include <stdio.h>
#define STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(COND)?1:-1]
struct foo {
	char cc[12];
	char bb[];
};

int main(void)
{
	//char b[] = {DSPOUET};
	struct foo a;
    //STATIC_ASSERT(sizeof(b)==3,pouet);
    fprintf(stderr, "sizeof (b) = %d\n", sizeof(a));
	//fprintf(stderr, "b= %s %d \n", b,sizeof(b));
	return 0;
}
