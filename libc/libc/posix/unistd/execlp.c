/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <errno.h>

int execvp(const char *file, char * const *argv);


int execlp(const char *file, const char *arg1, ...)
/* execlp("sh", "sh", "-c", "example", (char *) 0); */
{
	return execvp(file, (char * const *) &arg1);
}
