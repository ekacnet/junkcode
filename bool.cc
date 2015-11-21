#include <stdio.h>

int main(void)
{
    bool val = true;
    int v = 2;

    fprintf(stderr, "val = %d %d\n", val, ((bool)v) == val);
    return 0;
}
