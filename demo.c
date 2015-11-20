#include <stdio.h>
#include <string.h>

int main(void)
{
	char tab[4];
	int i;

	tab[0] = 0xfa;
	tab[1] = 0xf1;
	tab[2] = 0x74;
	tab[3] = 0x84;

	for(i = 0; i < sizeof(tab); i++) {
		fprintf(stdout, "%%02x gives %02x while  %%02hhx gives %02hhx\n", tab[i], tab[i]);
	}
	return 0;
}
