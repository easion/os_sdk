/* history.c, created from history.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/history.def"

#line 45 "d:/jicamasdk/progs/bash-2.05/builtins/history.def"

#include <config.h>

#if defined (HISTORY)
#include "../bashtypes.h"
#ifndef _MINIX
#  include <sys/file.h>
#endif
#include "posixstat.h"
#include "filecntl.h"
#include <errno.h>
#include <stdio.h>
#if defined (HAVE_UNISTD_H)
#  include <unistd.h>
#endif

#include "../bashansi.h"

#include "../shell.h"
#include "../bashhist.h"
#include <readline/history.h>
#include "bashgetopt.h"
#include "common.h"

#if !defined (errno)
extern int errno;
#endif

static void display_history __P((WORD_LIST *));
static int delete_histent __P((int));
static int delete_last_history __P((void));
static void push_history __P((WORD_LIST *));
static int expand_and_print_history __P((WORD_LIST *));

#define AFLAG	0x01
#define RFLAG	0x02
#define WFLAG	0x04
#define NFLAG	0x08
#define SFLAG	0x10
#define PFLAG	0x20
#define CFLAG	0x40
#define DFLAG	0x80

int
history_builtin (list)
     WORD_LIST *list;
{
  int flags, opt, result;
  char *filename, *delete_arg;
  long delete_offset;

  flags = 0;
  reset_internal_getopt ();
  while ((opt = internal_getopt (list, "acd:npsrw")) != -1)
    {
      switch (opt)
	{
	case 'a':
	  flags |= AFLAG;
	  break;
	case 'c':
	  flags |= CFLAG;
	  break;
	case 'n':
	  flags |= NFLAG;
	  break;
	case 'r':
	  flags |= RFLAG;
	  break;
	case 'w':
	  flags |= WFLAG;
	  break;
	case 's':
	  flags |= SFLAG;
	  break;
	case 'd':
	  flags |= DFLAG;
	  delete_arg = list_optarg;
	  break;
	case 'p':
#if defined (BANG_HISTORY)
	  flags |= PFLAG;
#endif
	  break;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }
  list = loptend;

  opt = flags & (AFLAG|RFLAG|WFLAG|NFLAG);
  if (opt && opt != AFLAG && opt != RFLAG && opt != WFLAG && opt != NFLAG)
    {
      builtin_error ("cannot use more than one of -anrw");
      return (EXECUTION_FAILURE);
    }

  /* clear the history, but allow other arguments to add to it again. */
  if (flags & CFLAG)
    {
      clear_history ();
      if (list == 0)
	return (EXECUTION_SUCCESS);
    }

  if (flags & SFLAG)
    {
      if (list)
	push_history (list);
      return (EXECUTION_SUCCESS);
    }
#if defined (BANG_HISTORY)
  else if (flags & PFLAG)
    {
      if (list)
	return (expand_and_print_history (list));
      return (EXECUTION_SUCCESS);
    }
#endif
  else if (flags & DFLAG)
    {
      if ((legal_number (delete_arg, &delete_offset) == 0)
	  || (delete_offset < history_base)
	  || (delete_offset > (history_base + history_length)))
	{
	  builtin_error ("%s: not a valid history position", delete_arg);
	  return (EXECUTION_FAILURE);
	}
      opt = delete_offset;
      result = delete_histent (opt - history_base);
      /* Since remove_history changes history_length, this can happen if
	 we delete the last history entry. */
      if (where_history () > history_length)
	history_set_pos (history_length);
      return (result ? EXECUTION_SUCCESS : EXECUTION_FAILURE);
    }
  else if ((flags & (AFLAG|RFLAG|NFLAG|WFLAG|CFLAG)) == 0)
    {
      display_history (list);
      return (EXECUTION_SUCCESS);
    }

  filename = list ? list->word->word : get_string_value ("HISTFILE");
  result = EXECUTION_SUCCESS;

  if (flags & AFLAG)		/* Append session's history to file. */
    result = maybe_append_history (filename);
  else if (flags & WFLAG)	/* Write entire history. */
    result = write_history (filename);
  else if (flags & RFLAG)	/* Read entire file. */
    result = read_history (filename);
  else if (flags & NFLAG)	/* Read `new' history from file. */
    {
      /* Read all of the lines in the file that we haven't already read. */
      using_history ();
      result = read_history_range (filename, history_lines_in_file, -1);
      using_history ();
      history_lines_in_file = where_history ();
    }

  return (result ? EXECUTION_FAILURE : EXECUTION_SUCCESS);
}

/* Accessors for HIST_ENTRY lists that are called HLIST. */
#define histline(i) (hlist[(i)]->line)
#define histdata(i) (hlist[(i)]->data)

static void
display_history (list)
     WORD_LIST *list;
{
  register int i;
  long limit;
  HIST_ENTRY **hlist;

  if (list)
    {
      limit = get_numeric_arg (list, 0);
      if (limit < 0)
	limit = -limit;
    }
  else
    limit = -1;

  hlist = history_list ();

  if (hlist)
    {
      for (i = 0;  hlist[i]; i++)
	;

      if (0 <= limit && limit < i)
	i -= limit;
      else
	i = 0;

      while (hlist[i])
	{
	  QUIT;
	  printf ("%5d%c %s\n", i + history_base,
		  histdata(i) ? '*' : ' ',
		  histline(i));
	  i++;
	}
    }
}

/* Delete and free the history list entry at offset I. */
static int
delete_histent (i)
     int i;
{
  HIST_ENTRY *discard;

  discard = remove_history (i);
  if (discard)
    {
      if (discard->line)
	free (discard->line);
      free ((char *) discard);
    }
  return 1;
}

static int
delete_last_history ()
{
  register int i;
  HIST_ENTRY **hlist, *histent;

  hlist = history_list ();
  if (hlist == NULL)
    return 0;

  for (i = 0; hlist[i]; i++)
    ;
  i--;

  /* History_get () takes a parameter that must be offset by history_base. */
  histent = history_get (history_base + i);	/* Don't free this */
  if (histent == NULL)
    return 0;

  return (delete_histent (i));
}

/* Remove the last entry in the history list and add each argument in
   LIST to the history. */
static void
push_history (list)
     WORD_LIST *list;
{
  char *s;

  if (hist_last_line_added && delete_last_history () == 0)
    return;
  s = string_list (list);
  maybe_add_history (s);	/* Obeys HISTCONTROL setting. */
  free (s);
}

#if defined (BANG_HISTORY)
static int
expand_and_print_history (list)
     WORD_LIST *list;
{
  char *s;
  int r, result;

  if (hist_last_line_added && delete_last_history () == 0)
    return EXECUTION_FAILURE;
  result = EXECUTION_SUCCESS;
  while (list)
    {
      r = history_expand (list->word->word, &s);
      if (r < 0)
	{
	  builtin_error ("%s: history expansion failed", list->word->word);
	  result = EXECUTION_FAILURE;
	}
      else
	{
	  fputs (s, stdout);
	  putchar ('\n');
	}
      FREE (s);
      list = list->next;
    }
  fflush (stdout);
  return result;
}
#endif /* BANG_HISTORY */
#endif /* HISTORY */
