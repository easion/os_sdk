/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>


long filelength(int stream)
{
	long cur, result;

	cur = lseek(stream, (off_t)0, SEEK_CUR);
	result = lseek(stream, (off_t)0, SEEK_END);
	lseek(stream, (off_t)cur, SEEK_SET);
	return result;
}

