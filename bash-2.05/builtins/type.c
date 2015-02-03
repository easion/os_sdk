/* type.c, created from type.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/type.def"

#line 43 "d:/jicamasdk/progs/bash-2.05/builtins/type.def"

#include <config.h>

#include "../bashtypes.h"
#include "posixstat.h"

#if defined (HAVE_UNISTD_H)
#  include <unistd.h>
#endif

#include <stdio.h>
#include "../bashansi.h"

#include "../shell.h"
#include "../findcmd.h"
#include "../hashcmd.h"

#if defined (ALIAS)
#include "../alias.h"
#endif /* ALIAS */

#include "common.h"
#include "bashgetopt.h"

extern int find_reserved_word __P((char *));

extern char *this_command_name;

/* For each word in LIST, find out what the shell is going to do with
   it as a simple command. i.e., which file would this shell use to
   execve, or if it is a builtin command, or an alias.  Possible flag
   arguments:
	-t		Returns the "type" of the object, one of
			`alias', `keyword', `function', `builtin',
			or `file'.

	-p		Returns the pathname of the file if -type is
			a file.

	-a		Returns all occurrences of words, whether they
			be a filename in the path, alias, function,
			or builtin.
   Order of evaluation:
	alias
	keyword
	function
	builtin
	file
 */

int
type_builtin (list)
     WORD_LIST *list;
{
  int path_only, type_only, all, verbose;
  int successful_finds, opt;
  WORD_LIST *prev, *this;

  if (list == 0)
    return (EXECUTION_SUCCESS);

  path_only = type_only = all = 0;
  successful_finds = 0;

  /* Handle the obsolescent `-type', `-path', and `-all' by prescanning
     the arguments and removing those options from the list before calling
     internal_getopt.  Recognize `--type', `--path', and `--all' also.
     THIS SHOULD REALLY GO AWAY. */
  for (this = list; this && this->word->word[0] == '-'; )
    {
      char *flag = &(this->word->word[1]);

      if (STREQ (flag, "type") || STREQ (flag, "-type"))
	{
	  type_only = 1;
	  path_only = 0;
	}
      else if (STREQ (flag, "path") || STREQ (flag, "-path"))
	{
	  path_only = 1;
	  type_only = 0;
	}
      else if (STREQ (flag, "all") || STREQ (flag, "-all"))
	all = 1;
      else
	{
	  prev = this;
	  this = this->next;
	  continue;
	}

      /* We found a long option; remove it from the argument list.  Don't
	 free it if it's the head of the argument list, though -- the
	 argument list will be freed by the caller. */
      if (this == list)
	this = list = list->next;
      else
	{
	  prev->next = this->next;
	  this->next = (WORD_LIST *)NULL;
	  dispose_words (this);
	  this = prev->next;
	}
    }

  reset_internal_getopt ();
  while ((opt = internal_getopt (list, "apt")) != -1)
    {
      switch (opt)
	{
	case 't':
	  type_only = 1;
	  path_only = 0;
	  break;
	case 'p':
	  path_only = 1;
	  type_only = 0;
	  break;
	case 'a':
	  all = 1;
	  break;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }
  list = loptend;

  if (type_only)
    verbose = 1;
  else if (path_only == 0)
    verbose = 2;
  else if (path_only)
    verbose = 3;
  else
    verbose = 0;

  while (list)
    {
      int found;

      found = describe_command (list->word->word, verbose, all);

      if (!found && !path_only && !type_only)
	builtin_error ("%s: not found", list->word->word);

      successful_finds += found;
      list = list->next;
    }

  fflush (stdout);

  return ((successful_finds != 0) ? EXECUTION_SUCCESS : EXECUTION_FAILURE);
}

/*
 * Describe COMMAND as required by the type builtin.
 *
 * If VERBOSE == 0, don't print anything
 * If VERBOSE == 1, print short description as for `type -t'
 * If VERBOSE == 2, print long description as for `type' and `command -V'
 * If VERBOSE == 3, print path name only for disk files
 * If VERBOSE == 4, print string used to invoke COMMAND, for `command -v'
 *
 * ALL says whether or not to look for all occurrences of COMMAND, or
 * return after finding it once.
 */
int
describe_command (command, verbose, all)
     char *command;
     int verbose, all;
{
  int found, i, found_file, f;
  char *full_path, *x;
  SHELL_VAR *func;
#if defined (ALIAS)
  alias_t *alias;
#endif

  found = found_file = 0;
  full_path = (char *)NULL;

#if defined (ALIAS)
  /* Command is an alias? */
  alias = find_alias (command);

  if (alias)
    {
      if (verbose == 1)
	puts ("alias");
      else if (verbose == 2)
	printf ("%s is aliased to `%s'\n", command, alias->value);
      else if (verbose == 4)
	{
	  x = sh_single_quote (alias->value);
	  printf ("alias %s=%s\n", command, x);
	  free (x);
	}

      found = 1;

      if (all == 0)
	return (1);
    }
#endif /* ALIAS */

  /* Command is a shell reserved word? */
  i = find_reserved_word (command);
  if (i >= 0)
    {
      if (verbose == 1)
	puts ("keyword");
      else if (verbose == 2)
	printf ("%s is a shell keyword\n", command);
      else if (verbose == 4)
	printf ("%s\n", command);

      found = 1;

      if (all == 0)
	return (1);
    }

  /* Command is a function? */
  func = find_function (command);

  if (func)
    {
      if (verbose == 1)
	puts ("function");
      else if (verbose == 2)
	{
#define PRETTY_PRINT_FUNC 1
	  char *result;

	  printf ("%s is a function\n", command);

	  /* We're blowing away THE_PRINTED_COMMAND here... */

	  result = named_function_string (command,
					  (COMMAND *) function_cell (func),
					  PRETTY_PRINT_FUNC);
	  printf ("%s\n", result);
#undef PRETTY_PRINT_FUNC
	}
      else if (verbose == 4)
	printf ("%s\n", command);

      found = 1;

      if (all == 0)
	return (1);
    }

  /* Command is a builtin? */
  if (find_shell_builtin (command))
    {
      if (verbose == 1)
	puts ("builtin");
      else if (verbose == 2)
	printf ("%s is a shell builtin\n", command);
      else if (verbose == 4)
	printf ("%s\n", command);

      found = 1;

      if (all == 0)
	return (1);
    }

  /* Command is a disk file? */
  /* If the command name given is already an absolute command, just
     check to see if it is executable. */
  if (absolute_program (command))
    {
      f = file_status (command);
      if (f & FS_EXECABLE)
	{
	  if (verbose == 1)
	    puts ("file");
	  else if (verbose == 2)
	    printf ("%s is %s\n", command, command);
	  else if (verbose == 3 || verbose == 4)
	    printf ("%s\n", command);

	  /* There's no use looking in the hash table or in $PATH,
	     because they're not consulted when an absolute program
	     name is supplied. */
	  return (1);
	}
    }

  /* If the user isn't doing "-a", then we might care about
     whether the file is present in our hash table. */
  if (all == 0)
    {
      if ((full_path = find_hashed_filename (command)) != (char *)NULL)
	{
	  if (verbose == 1)
	    puts ("file");
	  else if (verbose == 2)
	    printf ("%s is hashed (%s)\n", command, full_path);
	  else if (verbose == 3 || verbose == 4)
	    printf ("%s\n", full_path);

	  free (full_path);
	  return (1);
	}
    }

  /* Now search through $PATH. */
  while (1)
    {
      if (all == 0)
	full_path = find_user_command (command);
      else
	full_path =
	  user_command_matches (command, FS_EXEC_ONLY, found_file);
	  /* XXX - should that be FS_EXEC_PREFERRED? */

      if (!full_path)
	break;

      /* If we found the command as itself by looking through $PATH, it
	 probably doesn't exist.  Check whether or not the command is an
	 executable file.  If it's not, don't report a match. */
      if (STREQ (full_path, command))
	{
	  f = file_status (full_path);
	  if ((f & FS_EXECABLE) == 0)
	    {
	      free (full_path);
	      full_path = (char *)NULL;
	      if (all == 0)
		break;
	    }
	  else if (verbose >= 2)
	    full_path = sh_makepath ((char *)NULL, full_path, MP_DOCWD);
	}

      found_file++;
      found = 1;

      if (verbose == 1)
	puts ("file");
      else if (verbose == 2)
	printf ("%s is %s\n", command, full_path);
      else if (verbose == 3 || verbose == 4)
	printf ("%s\n", full_path);

      free (full_path);
      full_path = (char *)NULL;

      if (all == 0)
	break;
    }

  return (found);
}
