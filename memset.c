#include <stdio.h>

int main(void) {
	char tab[sizeof(int)];

	memset(tab, -1, sizeof(int));
	return 0;
}
