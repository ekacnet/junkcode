#include <stdio.h>


int main(void)
{
    char tab[] = {'\f\f', '\d8', '\2'};
    unsigned int i = 0;
    for (i = 0; i < sizeof(tab); i++) {
        fprintf(stderr, "tab[i] = %hhx\n");
    }
    return 0;
}
