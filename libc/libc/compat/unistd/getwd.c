/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <unistd.h>
#include <limits.h>

char* getpwd(unsigned char *stream, int sz);

char * __get_curdir(void ) {
	static char __cwd[512];
	return getpwd(__cwd,512); 
	}

char * getwd(char *buffer)
{
 if (buffer == 0) return 0;
 char * p=__get_curdir();
 strcpy(buffer,p);
 return buffer;
}
