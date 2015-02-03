/* help.c, created from help.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/help.def"

#line 34 "d:/jicamasdk/progs/bash-2.05/builtins/help.def"

#include <config.h>

#if defined (HELP_BUILTIN)
#include <stdio.h>

#if defined (HAVE_UNISTD_H)
#  ifdef _MINIX
#    include <sys/types.h>
#  endif
#  include <unistd.h>
#endif

#include "../shell.h"
#include "../builtins.h"
#include "../pathexp.h"
#include "common.h"
#include "bashgetopt.h"

#include <glob/strmatch.h>
#include <glob/glob.h>

static  void show_builtin_command_help __P((void));

/* Print out a list of the known functions in the shell, and what they do.
   If LIST is supplied, print out the list which matches for each pattern
   specified. */
int
help_builtin (list)
     WORD_LIST *list;
{
  register int i, j;
  char *pattern, *name;
  int plen, match_found, sflag;

  sflag = 0;
  reset_internal_getopt ();
  while ((i = internal_getopt (list, "s")) != -1)
    {
      switch (i)
	{
	case 's':
	  sflag = 1;
	  break;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }
  list = loptend;

  if (list == 0)
    {
      show_shell_version (0);
      show_builtin_command_help ();
      return (EXECUTION_SUCCESS);
    }

  /* We should consider making `help bash' do something. */

  if (glob_pattern_p (list->word->word))
    {
      printf ("Shell commands matching keyword%s `", list->next ? "s" : "");
      print_word_list (list, ", ");
      printf ("'\n\n");
    }

  for (match_found = 0, pattern = ""; list; list = list->next)
    {
      pattern = list->word->word;
      plen = strlen (pattern);

      for (i = 0; name = shell_builtins[i].name; i++)
	{
	  QUIT;
	  if ((strncmp (pattern, name, plen) == 0) ||
	      (strmatch (pattern, name, FNMATCH_EXTFLAG) != FNM_NOMATCH))
	    {
	      printf ("%s: %s\n", name, shell_builtins[i].short_doc);

	      if (sflag == 0)
		for (j = 0; shell_builtins[i].long_doc[j]; j++)
		  printf ("    %s\n", shell_builtins[i].long_doc[j]);

	      match_found++;
	    }
	}
    }

  if (match_found == 0)
    {
      builtin_error ("no help topics match `%s'.  Try `help help'.", pattern);
      return (EXECUTION_FAILURE);
    }

  fflush (stdout);
  return (EXECUTION_SUCCESS);
}

static void
show_builtin_command_help ()
{
  int i, j;
  char blurb[36];

  printf (
"These shell commands are defined internally.  Type `help' to see this list.\n\
Type `help name' to find out more about the function `name'.\n\
Use `info bash' to find out more about the shell in general.\n\
\n\
A star (*) next to a name means that the command is disabled.\n\
\n");

  for (i = 0; i < num_shell_builtins; i++)
    {
      QUIT;
      blurb[0] = (shell_builtins[i].flags & BUILTIN_ENABLED) ? ' ' : '*';
      strncpy (blurb + 1, shell_builtins[i].short_doc, 34);
      blurb[35] = '\0';
      printf ("%s", blurb);

      if (i % 2)
	printf ("\n");
      else
	for (j = strlen (blurb); j < 35; j++)
	  putc (' ', stdout);
    }
  if (i % 2)
    printf ("\n");
}
#endif /* HELP_BUILTIN */
