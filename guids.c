#include <stdint.h>
#include <xmmintrin.h>
#include <stdio.h>

struct GUID {
	uint32_t time_low;
	uint16_t time_mid;
	uint16_t time_hi_and_version;
	uint8_t clock_seq[2];
	uint8_t node[6];
}/* [gensize,noprint,public] */;

struct F {
	uint64_t p1;
	uint64_t p2;
};

int main(void) {
	struct GUID g1;
	struct GUID g2;
	fprintf(stderr, "test\n");

	fprintf(stderr, "res = %"PRIu64, ((uint64_t)(g1)) == ((uint64_t)(g2)));
}
