#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/types.h>
#include <net/if.h>
#include <net/if_arp.h>
#define inaddrr(x) ((struct sockaddr_in *) &pifr->x)->sin_addr

int main(void)
{
	struct ifreq ifr;
	struct ifreq* pifr = &ifr;
	struct sockaddr_in sa;
	fprintf(stdout, "ip = %s\n", inet_ntoa(inaddrr(ifr_addr)));
	return (0);

}
