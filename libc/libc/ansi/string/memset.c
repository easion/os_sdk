
#include <limits.h>
#include <string.h>

void *
memset(void *tov, int c, size_t len)
{
	register char *to = tov;

	while (len-- > 0)
		*to++ = c;

	return tov;
}

