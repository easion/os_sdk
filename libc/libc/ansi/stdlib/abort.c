
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char msg[] = "Abort!\r\n";

void
abort()
{
  write((int)stderr, msg, sizeof(msg)-1);
  //raise(SIGABRT);	/* this will generate traceback and won't return */
  _exit(1);
}