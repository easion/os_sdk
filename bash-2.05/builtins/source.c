/* source.c, created from source.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/source.def"

#line 37 "d:/jicamasdk/progs/bash-2.05/builtins/source.def"
/* source.c - Implements the `.' and `source' builtins. */

#include <config.h>

#include "../bashtypes.h"
#include "posixstat.h"
#include "filecntl.h"
#ifndef _MINIX
#  include <sys/file.h>
#endif
#include <errno.h>

#if defined (HAVE_UNISTD_H)
#  include <unistd.h>
#endif

#include "../bashansi.h"

#include "../shell.h"
#include "../findcmd.h"
#include "common.h"

#if !defined (errno)
extern int errno;
#endif /* !errno */

#if defined (RESTRICTED_SHELL)
extern int restricted;
#endif

/* If non-zero, `.' uses $PATH to look up the script to be sourced. */
int source_uses_path = 1;

/* If non-zero, `.' looks in the current directory if the filename argument
   is not found in the $PATH. */
int source_searches_cwd = 1;

/* If this . script is supplied arguments, we save the dollar vars and
   replace them with the script arguments for the duration of the script's
   execution.  If the script does not change the dollar vars, we restore
   what we saved.  If the dollar vars are changed in the script, and we are
   not executing a shell function, we leave the new values alone and free
   the saved values. */
static void
maybe_pop_dollar_vars ()
{
  if (variable_context == 0 && dollar_vars_changed ())
    {
      dispose_saved_dollar_vars ();
      set_dollar_vars_unchanged ();
    }
  else
    pop_dollar_vars ();
}

/* Read and execute commands from the file passed as argument.  Guess what.
   This cannot be done in a subshell, since things like variable assignments
   take place in there.  So, I open the file, place it into a large string,
   close the file, and then execute the string. */
int
source_builtin (list)
     WORD_LIST *list;
{
  int result;
  char *filename;

  if (list == 0)
    {
      builtin_error ("filename argument required");
      builtin_usage ();
      return (EX_USAGE);
    }

  if (no_options (list))
    return (EX_USAGE);

#if defined (RESTRICTED_SHELL)
  if (restricted && strchr (list->word->word, '/'))
    {
      builtin_error ("%s: restricted", list->word->word);
      return (EXECUTION_FAILURE);
    }
#endif

  filename = (char *)NULL;
  if (source_uses_path)
    filename = find_path_file (list->word->word);
  if (filename == 0)
    {
      if (source_searches_cwd == 0)
	{
	  builtin_error ("%s: file not found", list->word->word);
	  return (EXECUTION_FAILURE);
	}
      else
	filename = savestring (list->word->word);
    }

  begin_unwind_frame ("source");
  add_unwind_protect ((Function *)xfree, filename);

  if (list->next)
    {
      push_dollar_vars ();
      add_unwind_protect ((Function *)maybe_pop_dollar_vars, (char *)NULL);
      remember_args (list->next, 1);
    }
  set_dollar_vars_unchanged ();

  result = source_file (filename);

  run_unwind_frame ("source");

  return (result);
}
