/* exec.c, created from exec.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/exec.def"

#line 36 "d:/jicamasdk/progs/bash-2.05/builtins/exec.def"

#include <config.h>

#include "../bashtypes.h"
#include "posixstat.h"
#include <signal.h>
#include <errno.h>

#if defined (HAVE_UNISTD_H)
#  include <unistd.h>
#endif

#include "../bashansi.h"

#include "../shell.h"
#include "../execute_cmd.h"
#include "../findcmd.h"
#if defined (JOB_CONTROL)
#  include "../jobs.h"
#endif
#include "../flags.h"
#include "../trap.h"
#if defined (HISTORY)
#  include "../bashhist.h"
#endif
#include "common.h"
#include "bashgetopt.h"

/* Not all systems declare ERRNO in errno.h... and some systems #define it! */
#if !defined (errno)
extern int errno;
#endif /* !errno */

extern int subshell_environment;
extern REDIRECT *redirection_undo_list;

int no_exit_on_failed_exec;

/* If the user wants this to look like a login shell, then
   prepend a `-' onto NAME and return the new name. */
static char *
mkdashname (name)
     char *name;
{
  char *ret;

  ret = (char *)xmalloc (2 + strlen (name));
  ret[0] = '-';
  strcpy (ret + 1, name);
  return ret;
}

int
exec_builtin (list)
     WORD_LIST *list;
{
  int exit_value = EXECUTION_FAILURE;
  int cleanenv, login, opt;
  char *argv0, *command, **args, **env, *newname, *com2;

  cleanenv = login = 0;
  argv0 = (char *)NULL;

  reset_internal_getopt ();
  while ((opt = internal_getopt (list, "cla:")) != -1)
    {
      switch (opt)
	{
	case 'c':
	  cleanenv = 1;
	  break;
	case 'l':
	  login = 1;
	  break;
	case 'a':
	  argv0 = list_optarg;
	  break;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }
  list = loptend;

  /* First, let the redirections remain. */
  dispose_redirects (redirection_undo_list);
  redirection_undo_list = (REDIRECT *)NULL;

  if (list == 0)
    return (EXECUTION_SUCCESS);

#if defined (RESTRICTED_SHELL)
  if (restricted)
    {
      builtin_error ("restricted");
      return (EXECUTION_FAILURE);
    }
#endif /* RESTRICTED_SHELL */

  args = word_list_to_argv (list, 1, 0, (int *)NULL);

  /* A command with a slash anywhere in its name is not looked up in $PATH. */
  command = absolute_program (args[0]) ? args[0] : search_for_command (args[0]);

  if (command == 0)
    {
      builtin_error ("%s: not found", args[0]);
      exit_value = EX_NOTFOUND;	/* As per Posix.2, 3.14.6 */
      goto failed_exec;
    }

  com2 = full_pathname (command);
  if (com2)
    {
      if (command != args[0])
	free (command);
      command = com2;
    }

  if (argv0)
    {
      free (args[0]);
      args[0] = login ? mkdashname (argv0) : savestring (argv0);
    }
  else if (login)
    {
      newname = mkdashname (args[0]);
      free (args[0]);
      args[0] = newname;
    }

  /* Decrement SHLVL by 1 so a new shell started here has the same value,
     preserving the appearance.  After we do that, we need to change the
     exported environment to include the new value. */
  if (cleanenv == 0)
    adjust_shell_level (-1);

  if (cleanenv)
    env = (char **)NULL;
  else
    {	
      maybe_make_export_env ();
      env = export_env;
    }

#if defined (HISTORY)
  if (interactive_shell && subshell_environment == 0)
    maybe_save_shell_history ();
#endif /* HISTORY */

  restore_original_signals ();

#if defined (JOB_CONTROL)
  if (subshell_environment == 0)
    end_job_control ();
#endif /* JOB_CONTROL */

  shell_execve (command, args, env);

  /* We have to set this to NULL because shell_execve has called realloc()
     to stuff more items at the front of the array, which may have caused
     the memory to be freed by realloc().  We don't want to free it twice. */
  args = (char **)NULL;
  if (cleanenv == 0)
    adjust_shell_level (1);

  if (executable_file (command) == 0)
    {
      builtin_error ("%s: cannot execute: %s", command, strerror (errno));
      exit_value = EX_NOEXEC;	/* As per Posix.2, 3.14.6 */
    }
  else
    file_error (command);

failed_exec:
  if (command)
    free (command);

  if (subshell_environment || (interactive == 0 && no_exit_on_failed_exec == 0))
    exit_shell (exit_value);

  if (args)
    free_array (args);

  initialize_traps ();
  reinitialize_signals ();

#if defined (JOB_CONTROL)
  restart_job_control ();
#endif /* JOB_CONTROL */

  return (exit_value);
}
