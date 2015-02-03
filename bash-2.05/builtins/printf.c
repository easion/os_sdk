/* printf.c, created from printf.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/printf.def"

#line 36 "d:/jicamasdk/progs/bash-2.05/builtins/printf.def"

#include <config.h>

#include "../bashtypes.h"

#include <errno.h>
#if defined (HAVE_LIMITS_H)
#  include <limits.h>
#else
   /* Assume 32-bit ints. */
#  define INT_MAX		2147483647
#  define INT_MIN		(-2147483647-1)
#endif

#include <stdio.h>
#include <chartypes.h>

#ifdef HAVE_INTTYPES_H
#  include <inttypes.h>
#endif

#include "../bashansi.h"

#define NEED_STRTOIMAX_DECL

#include "../shell.h"
#include "stdc.h"
#include "bashgetopt.h"
#include "common.h"

/* This should use the ISO C constant format strings; I'll do that later. */
#if SIZEOF_LONG < SIZEOF_LONG_LONG
#  define INTMAX_CONV	"ll"
#else
#  define INTMAX_CONV	"l"
#endif

#if !defined (errno)
extern int errno;
#endif

#define PF(f, func) \
  do { \
    if (have_fieldwidth && have_precision) \
      tw += printf(f, fieldwidth, precision, func); \
    else if (have_fieldwidth) \
      tw += printf(f, fieldwidth, func); \
    else if (have_precision) \
      tw += printf(f, precision, func); \
    else \
      tw += printf(f, func); \
  } while (0)

/* We free the buffer used by mklong() if it's `too big'. */
#define PRETURN(value) \
  do \
    { \
      if (conv_bufsize > 4096 ) \
	{ \
	  free(conv_buf); \
	  conv_bufsize = 0; \
	  conv_buf = 0; \
	} \
      fflush (stdout); \
      return (value); \
    } \
  while (0)

#define SKIP1 "#'-+ 0"
#define LENMODS "hjlLtz"

static void printstr __P((char *, char *, int, int, int));
static int tescape __P((char *, int, char *, int *));
static char *bexpand __P((char *, int, int *, int *));
static char *mklong __P((char *, char *));
static int getchr __P((void));
static char *getstr __P((void));
static int  getint __P((void));
static long getlong __P((void));
static unsigned long getulong __P((void));
#if defined (HAVE_LONG_LONG)
static long long getllong __P((void));
static unsigned long long getullong __P((void));
#endif
static intmax_t getintmax __P((void));
static uintmax_t getuintmax __P((void));
static double getdouble __P((void));
#if defined (HAVE_LONG_DOUBLE) && HAVE_DECL_STRTOLD
static long double getldouble __P((void));
#endif
static int asciicode __P((void));

static WORD_LIST *garglist;
static int retval;
static int conversion_error;

static char *conv_buf;
static size_t conv_bufsize;

int
printf_builtin (list)
     WORD_LIST *list;
{
  int ch, fieldwidth, precision;
  int have_fieldwidth, have_precision;
  long tw;
  char convch, thisch, nextch, *format, *modstart, *fmt, *start;

  conversion_error = 0;
  retval = EXECUTION_SUCCESS;
  reset_internal_getopt ();
  if (internal_getopt (list, "") != -1)
    {
      builtin_usage();
      return (EX_USAGE);
    }
  list = loptend;

  if (list == 0)
    {
      builtin_usage ();
      return (EX_USAGE);
    }

  if (list->word->word == 0 || list->word->word[0] == '\0')
    return (EXECUTION_SUCCESS);

  format = list->word->word;

  garglist = list->next;

  /* If the format string is empty after preprocessing, return immediately. */
  if (format == 0 || *format == 0)
    return (EXECUTION_SUCCESS);
	  
  /* Basic algorithm is to scan the format string for conversion
     specifications -- once one is found, find out if the field
     width or precision is a '*'; if it is, gather up value.  Note,
     format strings are reused as necessary to use up the provided
     arguments, arguments of zero/null string are provided to use
     up the format string. */
  do
    {
      tw = 0;
      /* find next format specification */
      for (fmt = format; *fmt; fmt++)
	{
	  precision = fieldwidth = 0;
	  have_fieldwidth = have_precision = 0;


	  if (*fmt == '\\')
	    {
	      fmt++;
	      /* A NULL fourth argument to tescape means to not do special
		 processing for \c. */
	      fmt += tescape (fmt, 1, &nextch, (int *)NULL);
	      putchar (nextch);
	      fmt--;	/* for loop will increment it for us again */
	      continue;
	    }

	  if (*fmt != '%')
	    {
	      putchar (*fmt);
	      continue;
	    }

	  /* ASSERT(*fmt == '%') */
	  start = fmt++;

	  if (*fmt == '%')		/* %% prints a % */
	    {
	      putchar ('%');
	      continue;
	    }

	  /* found format specification, skip to field width */
	  for (; *fmt && strchr(SKIP1, *fmt); ++fmt)
	    ;

	  /* Skip optional field width. */
	  if (*fmt == '*')
	    {
	      fmt++;
	      have_fieldwidth = 1;
	      fieldwidth = getint ();
	    }
	  else
	    while (DIGIT (*fmt))
	      fmt++;

	  /* Skip optional '.' and precision */
	  if (*fmt == '.')
	    {
	      ++fmt;
	      if (*fmt == '*')
		{
		  fmt++;
		  have_precision = 1;
		  precision = getint ();
		}
	      else
		while (DIGIT (*fmt))
		  fmt++;
	    }

	  /* skip possible format modifiers */
	  modstart = fmt;
	  while (*fmt && strchr (LENMODS, *fmt))
	    fmt++;
	    
	  if (*fmt == 0)
	    {
	      builtin_error ("`%s': missing format character", start);
	      PRETURN (EXECUTION_FAILURE);
	    }

	  convch = *fmt;
	  thisch = modstart[0];
	  nextch = modstart[1];
	  modstart[0] = convch;
	  modstart[1] = '\0';

	  switch(convch)
	    {
	    case 'c':
	      {
		char p;

		p = getchr ();
		PF(start, p);
		break;
	      }

	    case 's':
	      {
		char *p;

		p = getstr ();
		PF(start, p);
		break;
	      }

	    case 'n':
	      {
		char *var;

		var = getstr ();
		if (var && *var)
		  {
		    if (legal_identifier (var))
		      bind_var_to_int (var, tw);
		    else
		      {
			builtin_error ("%s: invalid variable name", var);
			PRETURN (EXECUTION_FAILURE);
		      }
		  }
		break;
	      }

	    case 'b':		/* expand escapes in argument */
	      {
		char *p, *xp;
		int rlen;

		p = getstr ();
		ch = rlen = 0;
		xp = bexpand (p, strlen (p), &ch, &rlen);

		if (xp)
		  {
		    /* Have to use printstr because of possible NUL bytes
		       in XP -- printf does not handle that well. */
		    printstr (start, xp, rlen, fieldwidth, precision);
		    free (xp);
		  }

		if (ch)
		  PRETURN (retval);
		break;
	      }

	    case 'q':		/* print with shell quoting */
	      {
		char *p, *xp;

		p = getstr ();
		xp = sh_backslash_quote (p);
		if (xp)
		  {
		    /* Use printstr to get fieldwidth and precision right. */
		    printstr (start, xp, strlen (xp), fieldwidth, precision);
		    free (xp);
		  }
		break;
	      }

	    case 'd':
	    case 'i':
	      {
		char *f;
#if defined (HAVE_LONG_LONG)
		if (thisch == 'l' && nextch == 'l')
		  {
		    long long p;

		    p = getllong ();
		    f = mklong (start, "ll");
		    PF(f, p);
		  }
		else
#endif
		if (thisch == 'j')
		  {
		    intmax_t p;

		    p = getintmax ();
		    f = mklong (start, INTMAX_CONV);
		    PF(f, p);
		  }
		else
		  {
		    long p;

		    p = getlong ();
		    f = mklong (start, "l");
		    PF(f, p);
		  }
		break;
	      }

	    case 'o':
	    case 'u':
	    case 'x':
	    case 'X':
	      {
		char *f;
#if defined (HAVE_LONG_LONG)
		if (thisch == 'l' && nextch == 'l')
		  {
		    unsigned long long p;

		    p = getullong ();
		    f = mklong (start, "ll");
		    PF(f, p);
		  }
		else
#endif
		if (thisch == 'j')
		  {
		    uintmax_t p;

		    p = getuintmax ();
		    f = mklong (start, INTMAX_CONV);
		    PF(f, p);
		  }
		else
		  {
		    unsigned long p;

		    p = getulong ();
		    f = mklong (start, "l");
		    PF (f, p);
		  }
		break;
	      }

	    case 'e':
	    case 'E':
	    case 'f':
	    case 'F':
	    case 'g':
	    case 'G':
#if defined (HAVE_PRINTF_A_FORMAT)
	    case 'a':
	    case 'A':
#endif
	      {
		char *f;
#if defined (HAVE_LONG_DOUBLE) && HAVE_DECL_STRTOLD
		if (thisch == 'L')
		  {
		    long double p;

		    p = getldouble ();
		    f = mklong (start, "L");
		    PF (f, p);
		  }
		else
#endif
		  {
		    double p;

		    p = getdouble ();
		    f = mklong (start, "");
		    PF (f, p);
		  }
		break;
	      }

	    /* We don't output unrecognized format characters; we print an
	       error message and return a failure exit status. */
	    default:
	      builtin_error ("`%c': invalid format character", convch);
	      PRETURN (EXECUTION_FAILURE);
	    }

	  modstart[0] = thisch;
	  modstart[1] = nextch;
	}
    }
  while (garglist && garglist != list->next);

  if (conversion_error)
    retval = EXECUTION_FAILURE;

  PRETURN (retval);
}

/* We duplicate a lot of what printf(3) does here. */
static void
printstr (fmt, string, len, fieldwidth, precision)
     char *fmt;			/* format */
     char *string;		/* expanded string argument */
     int len;			/* length of expanded string */
     int fieldwidth;		/* argument for width of `*' */
     int precision;		/* argument for precision of `*' */
{
#if 0
  char *s;
#endif
  int padlen, nc, ljust, i;
  int fw, pr;			/* fieldwidth and precision */

  if (string == 0 || *string == '\0')
    return;

#if 0
  s = fmt;
#endif
  if (*fmt == '%')
    fmt++;

  ljust = fw = 0;
  pr = -1;

  /* skip flags */
  while (strchr (SKIP1, *fmt))
    {
      if (*fmt == '-')
	ljust = 1;
      fmt++;
    }

  /* get fieldwidth, if present */
  if (*fmt == '*')
    {
      fmt++;
      fw = fieldwidth;
      if (fw < 0)
	{
	  fw = -fw;
	  ljust = 1;
	}
    }
  else if (DIGIT (*fmt))
    {
      fw = *fmt++ - '0';
      while (DIGIT (*fmt))
	fw = (fw * 10) + (*fmt++ - '0');
    }

  /* get precision, if present */
  if (*fmt == '.')
    {
      fmt++;
      if (*fmt == '*')
	{
	  fmt++;
	  pr = precision;
	}
      else if (DIGIT (*fmt))
	{
	  pr = *fmt++ - '0';
	  while (DIGIT (*fmt))
	    pr = (pr * 10) + (*fmt++ - '0');
	}
    }

#if 0
  /* If we remove this, get rid of `s'. */
  if (*fmt != 'b' && *fmt != 'q')
    {
      internal_error ("format parsing problem: %s", s);
      fw = pr = 0;
    }
#endif

  /* chars from string to print */
  nc = (pr >= 0 && pr <= len) ? pr : len;

  padlen = fw - nc;
  if (padlen < 0)
    padlen = 0;
  if (ljust)
    padlen = -padlen;

  /* leading pad characters */
  for (; padlen > 0; padlen--)
    putchar (' ');

  /* output NC characters from STRING */
  for (i = 0; i < nc; i++)
    putchar (string[i]);

  /* output any necessary trailing padding */
  for (; padlen < 0; padlen++)
    putchar (' ');
}
  
/* Convert STRING by expanding the escape sequences specified by the
   POSIX standard for printf's `%b' format string.  If SAWC is non-null,
   recognize `\c' and use that as a string terminator.  If we see \c, set
   *SAWC to 1 before returning.  LEN is the length of STRING. */

/* Translate a single backslash-escape sequence starting at ESTART (the
   character after the backslash) and return the number of characters
   consumed by the sequence.  CP is the place to return the translated
   value.  *SAWC is set to 1 if the escape sequence was \c, since that means
   to short-circuit the rest of the processing.  If SAWC is null, we don't
   do the \c short-circuiting, and \c is treated as an unrecognized escape
   sequence.  */
static int
tescape (estart, trans_squote, cp, sawc)
     char *estart;
     int trans_squote;
     char *cp;
     int *sawc;
{
  register char *p;
  int temp, c, evalue;

  p = estart;

  switch (c = *p++)
    {
#if defined (__STDC__)
      case 'a': *cp = '\a'; break;
#else
      case 'a': *cp = '\007'; break;
#endif

      case 'b': *cp = '\b'; break;

      case 'e':
      case 'E': *cp = '\033'; break;	/* ESC -- non-ANSI */

      case 'f': *cp = '\f'; break;

      case 'n': *cp = '\n'; break;

      case 'r': *cp = '\r'; break;

      case 't': *cp = '\t'; break;

      case 'v': *cp = '\v'; break;

      /* %b octal constants are `\0' followed by one, two, or three
	 octal digits... */
      case '0':
	for (temp = 3, evalue = 0; ISOCTAL (*p) && temp--; p++)
	  evalue = (evalue * 8) + OCTVALUE (*p);
	*cp = evalue & 0xFF;
	break;

      /* but, as an extension, the other echo-like octal escape
	 sequences are supported as well. */
      case '1': case '2': case '3': case '4':
      case '5': case '6': case '7':
	for (temp = 2, evalue = c - '0'; ISOCTAL (*p) && temp--; p++)
	  evalue = (evalue * 8) + OCTVALUE (*p);
	*cp = evalue & 0xFF;
	break;

      /* And, as another extension, we allow \xNNN, where each N is a
	 hex digit. */
      case 'x':
	for (temp = 2, evalue = 0; ISXDIGIT ((unsigned char)*p) && temp--; p++)
	  evalue = (evalue * 16) + HEXVALUE (*p);
	if (temp == 2)
	  {
	    builtin_error ("missing hex digit for \\x");
	    *cp = '\\';
	    return 0;
	  }
	*cp = evalue & 0xFF;
	break;

      case '\\':	/* \\ -> \ */
	*cp = c;
	break;

      case '\'':	/* TRANS_SQUOTE != 0 means \' -> ' */
	if (trans_squote)
	  *cp = c;
	else
	  {
	    *cp = '\\';
	    return 0;
	  }
	break;

      case 'c':
	if (sawc)
	  {
	    *sawc = 1;
	    break;
	  }
      /* other backslash escapes are passed through unaltered */
      default:
	*cp = '\\';
	return 0;
      }
  return (p - estart);
}

static char *
bexpand (string, len, sawc, lenp)
     char *string;
     int len, *sawc, *lenp;
{
  int temp;
  char *ret, *r, *s, c;

  if (string == 0 || *string == '\0')
    {
      if (sawc)
	*sawc = 0;
      if (lenp)
	*lenp = 0;
      return ((char *)NULL);
    }

  ret = (char *)xmalloc (len + 1);
  for (r = ret, s = string; s && *s; )
    {
      c = *s++;
      if (c != '\\' || *s == '\0')
	{
	  *r++ = c;
	  continue;
	}
      temp = 0;
      s += tescape (s, 0, &c, &temp);
      if (temp)
	{
	  if (sawc)
	    *sawc = 1;
	  break;
	}

      *r++ = c;
    }

  *r = '\0';
  if (lenp)
    *lenp = r - ret;
  return ret;
}

static char *
mklong (str, modifiers)
     char *str;
     char *modifiers;
{
  size_t len, slen, mlen;

  slen = strlen (str);
  mlen = strlen (modifiers);
  len = slen + mlen + 1;

  if (len > conv_bufsize)
    {
      conv_bufsize = (((len + 1023) >> 10) << 10);
      conv_buf = (char *)xrealloc (conv_buf, conv_bufsize);
    }

  FASTCOPY (str, conv_buf, slen - 1);
  FASTCOPY (modifiers, conv_buf + slen - 1, mlen);

  conv_buf[len - 2] = str[slen - 1];
  conv_buf[len - 1] = '\0';
  return (conv_buf);
}

static int
getchr ()
{
  int ret;

  if (garglist == 0)
    return ('\0');

  ret = (int)garglist->word->word[0];
  garglist = garglist->next;
  return ret;
}

static char *
getstr ()
{
  char *ret;

  if (garglist == 0)
    return ("");

  ret = garglist->word->word;
  garglist = garglist->next;
  return ret;
}

static int
getint ()
{
  long ret;

  ret = getlong ();

  if (ret > INT_MAX)
    {
      builtin_error ("warning: %s: %s", garglist->word->word, strerror(ERANGE));
      ret = INT_MAX;
    }
  else if (ret < INT_MIN)
    {
      builtin_error ("warning: %s: %s", garglist->word->word, strerror(ERANGE));
      ret = INT_MIN;
    }

  return ((int)ret);
}

static long
getlong ()
{
  long ret;
  char *ep;

  if (garglist == 0)
    return (0);

  if (garglist->word->word[0] == '\'' || garglist->word->word[0] == '"')
    return asciicode ();

  errno = 0;
  ret = strtol (garglist->word->word, &ep, 0);

  if (*ep)
    {
      builtin_error ("%s: invalid number", garglist->word->word);
      /* POSIX.2 says ``...a diagnostic message shall be written to standard
	 error, and the utility shall not exit with a zero exit status, but
	 shall continue processing any remaining operands and shall write the
         value accumulated at the time the error was detected to standard
	 output.''  Yecch. */
      ret = 0;
      conversion_error = 1;
    }
  else if (errno == ERANGE)
    builtin_error ("warning: %s: %s", garglist->word->word, strerror(ERANGE));

  garglist = garglist->next;
  return (ret);
}

static unsigned long
getulong ()
{
  unsigned long ret;
  char *ep;

  if (garglist == 0)
    return (0);

  if (garglist->word->word[0] == '\'' || garglist->word->word[0] == '"')
    return asciicode ();

  errno = 0;
  ret = strtoul (garglist->word->word, &ep, 0);
  
  if (*ep)
    {
      builtin_error ("%s: invalid number", garglist->word->word);
      /* Same thing about POSIX.2 conversion error requirements as getlong(). */
      ret = 0;
      conversion_error = 1;
    }
  else if (errno == ERANGE)
    builtin_error ("warning: %s: %s", garglist->word->word, strerror(ERANGE));

  garglist = garglist->next;
  return (ret);
}

#if defined (HAVE_LONG_LONG)

static long long
getllong ()
{
  long long ret;
  char *ep;

  if (garglist == 0)
    return (0);

  if (garglist->word->word[0] == '\'' || garglist->word->word[0] == '"')
    return asciicode ();

  errno = 0;
  ret = strtoll (garglist->word->word, &ep, 0);

  if (*ep)
    {
      builtin_error ("%s: invalid number", garglist->word->word);
      /* POSIX.2 says ``...a diagnostic message shall be written to standard
	 error, and the utility shall not exit with a zero exit status, but
	 shall continue processing any remaining operands and shall write the
         value accumulated at the time the error was detected to standard
	 output.''  Yecch. */
      ret = 0;
      conversion_error = 1;
    }
  else if (errno == ERANGE)
    builtin_error ("warning: %s: %s", garglist->word->word, strerror(ERANGE));

  garglist = garglist->next;
  return (ret);
}

static unsigned long long
getullong ()
{
  unsigned long long ret;
  char *ep;

  if (garglist == 0)
    return (0);

  if (garglist->word->word[0] == '\'' || garglist->word->word[0] == '"')
    return asciicode ();

  errno = 0;
  ret = strtoull (garglist->word->word, &ep, 0);
  
  if (*ep)
    {
      builtin_error ("%s: invalid number", garglist->word->word);
      /* Same thing about POSIX.2 conversion error requirements as getlong(). */
      ret = 0;
      conversion_error = 1;
    }
  else if (errno == ERANGE)
    builtin_error ("warning: %s: %s", garglist->word->word, strerror(ERANGE));

  garglist = garglist->next;
  return (ret);
}

#endif /* HAVE_LONG_LONG */

static intmax_t
getintmax ()
{
  intmax_t ret;
  char *ep;

  if (garglist == 0)
    return (0);

  if (garglist->word->word[0] == '\'' || garglist->word->word[0] == '"')
    return asciicode ();

  errno = 0;
  ret = strtoimax (garglist->word->word, &ep, 0);

  if (*ep)
    {
      builtin_error ("%s: invalid number", garglist->word->word);
      /* POSIX.2 says ``...a diagnostic message shall be written to standard
	 error, and the utility shall not exit with a zero exit status, but
	 shall continue processing any remaining operands and shall write the
         value accumulated at the time the error was detected to standard
	 output.''  Yecch. */
      ret = 0;
      conversion_error = 1;
    }
  else if (errno == ERANGE)
    builtin_error ("warning: %s: %s", garglist->word->word, strerror(ERANGE));

  garglist = garglist->next;
  return (ret);
}

static uintmax_t
getuintmax ()
{
  uintmax_t ret;
  char *ep;

  if (garglist == 0)
    return (0);

  if (garglist->word->word[0] == '\'' || garglist->word->word[0] == '"')
    return asciicode ();

  errno = 0;
  ret = strtoumax (garglist->word->word, &ep, 0);
  
  if (*ep)
    {
      builtin_error ("%s: invalid number", garglist->word->word);
      /* Same thing about POSIX.2 conversion error requirements as getlong(). */
      ret = 0;
      conversion_error = 1;
    }
  else if (errno == ERANGE)
    builtin_error ("warning: %s: %s", garglist->word->word, strerror(ERANGE));

  garglist = garglist->next;
  return (ret);
}

static double
getdouble ()
{
  double ret;
  char *ep;

  if (garglist == 0)
    return (0);

  if (garglist->word->word[0] == '\'' || garglist->word->word[0] == '"')
    return asciicode ();

  errno = 0;
  ret = strtod (garglist->word->word, &ep);

  if (*ep)
    {
      builtin_error ("%s: invalid number", garglist->word->word);
      /* Same thing about POSIX.2 conversion error requirements. */
      ret = 0;
      conversion_error = 1;
    }
  else if (errno == ERANGE)
    builtin_error ("warning: %s: %s", garglist->word->word, strerror(ERANGE));

  garglist = garglist->next;
  return (ret);
}

#if defined (HAVE_LONG_DOUBLE) && HAVE_DECL_STRTOLD
static long double
getldouble ()
{
  long double ret;
  char *ep;

  if (garglist == 0)
    return (0);

  if (garglist->word->word[0] == '\'' || garglist->word->word[0] == '"')
    return (asciicode ());

  errno = 0;
  ret = strtold (garglist->word->word, &ep);

  if (*ep)
    {
      builtin_error ("%s: invalid number", garglist->word->word);
      /* Same thing about POSIX.2 conversion error requirements. */
      ret = 0;
      conversion_error = 1;
    }
  else if (errno == ERANGE)
    builtin_error ("warning: %s: %s", garglist->word->word, strerror(ERANGE));

  garglist = garglist->next;
  return (ret);
}
#endif /* HAVE_LONG_DOUBLE && HAVE_DECL_STRTOLD */

/* NO check is needed for garglist here. */
static int
asciicode ()
{
  register int ch;

  ch = garglist->word->word[1];
  garglist = garglist->next;
  return (ch);
}
