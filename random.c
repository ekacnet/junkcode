#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <linux/random.h>

int main(void)
{
    int randFd = open("/dev/urandom", O_RDWR);
    int randcnt;
    ioctl(randFd, RNDGETENTCNT, &randcnt);
    fprintf(stderr, "entroy = %d\n", randcnt);
}
