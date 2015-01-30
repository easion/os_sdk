#include <libc/bss.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <sys/stat.h>
#include <dir.h>

int _rename(const char *n1, const char *n2);

int rename(const char *old, const char *_new)
{
 errno=_rename(old, _new);
 return errno;
}
