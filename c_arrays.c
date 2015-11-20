#include <stdio.h>

int main(void)
{
    const char* chars[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."};
    unsigned int idx = 0;

    for(idx = 0; idx <= (sizeof(chars) - 1);) {
        fprintf(stderr, "c = %s", chars[idx++]);
    }
    return 0;

}
