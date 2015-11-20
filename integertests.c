#include <stdio.h>
int main() {
	unsigned int i = 0;
	fprintf(stderr, "i=%u\n", i--);
	fprintf(stderr, "i=%u\n", i--);

}
