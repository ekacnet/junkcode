#include <stdio.h>
#include <stdint.h>

int main(void)
{
	uint64_t v64;
	uint32_t v1 = 0xAAAAAAAA;
	uint32_t v2 = 0x55555555;
	v64 = v1;
	v64 = (v64<<32) + v2;
	fprintf(stderr, "%lx\n",v64);
	return 0;
}
