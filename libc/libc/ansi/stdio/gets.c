/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>

char *
djgets(char *s)
{
  int c;
  char *cs;

  cs = s;
  while ((c = getchar()) != '\n' && c != EOF)
    *cs++ = c;
  if (c == EOF && cs==s)
    return NULL;
  *cs++ = '\0';
  return s;
}

/*
 * Read a line from stdin.
 * XXX Cooking should be done by getchar, not by us.
 * But what about handling backspace?
 * If getchar does the backspacing
 * then we can't keep it from going over our prompt.
 */
char *
gets(char *buf)
{
	int i;
	int c;

	i = 0;
	while (1) {
		c = getchar();
		if (c == EOF)
			break;
		if (c == '\r' || c == '\n') {
			/* The FreeBSD manpage says:
			 * The gets() function is equivalent to fgets() 
			 * with an infinite size and a stream of stdin, 
			 * except that the newline character (if any) 
			 * is not stored in the string.
			 */
			putchar('\n');
			break;
		}
		if (c == '\b' || c == 0x7f) {
			if (i > 0) {
				putchar('\b');
				putchar(' ');
				putchar('\b');
				i--;
			}
			continue;
		}
		buf[i++] = c;
		putchar(c);
	}

	buf[i] = '\0';
	return buf;
}


