#include <string.h>
static char *find_needle(const char *haystack)
{
	size_t i;
	for (i = 0; i < strlen(haystack); i++)
	if (memcmp("needle", haystack+i, strlen("needle")) == 0)
		return (char *)(haystack+i);
	return NULL;
}
