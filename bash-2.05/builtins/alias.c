/* alias.c, created from alias.def. */
#line 34 "d:/jicamasdk/progs/bash-2.05/builtins/alias.def"

#include <config.h>

#if defined (ALIAS)

#if defined (HAVE_UNISTD_H)
#  ifdef _MINIX
#    include <sys/types.h>
#  endif
#  include <unistd.h>
#endif

#  include "../bashansi.h"

#  include <stdio.h>
#  include "../shell.h"
#  include "../alias.h"
#  include "common.h"
#  include "bashgetopt.h"

static void print_alias __P((alias_t *));

/* Hack the alias command in a Korn shell way. */
int
alias_builtin (list)
     WORD_LIST *list;
{
  int any_failed, offset, pflag;
  alias_t **alias_list, *t;
  char *name, *value;

  pflag = 0;
  reset_internal_getopt ();
  while ((offset = internal_getopt (list, "p")) != -1)
    {
      switch (offset)
	{
	case 'p':
	  pflag = 1;
	  break;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }

  list = loptend;

  if (list == 0 || pflag)
    {
      if (aliases == 0)
	return (EXECUTION_SUCCESS);

      alias_list = all_aliases ();

      if (alias_list == 0)
	return (EXECUTION_SUCCESS);

      for (offset = 0; alias_list[offset]; offset++)
	print_alias (alias_list[offset]);

      free (alias_list);	/* XXX - Do not free the strings. */

      if (list == 0)
	return (EXECUTION_SUCCESS);
    }

  any_failed = 0;
  while (list)
    {
      name = list->word->word;

      for (offset = 0; name[offset] && name[offset] != '='; offset++)
	;

      if (offset && name[offset] == '=')
	{
	  name[offset] = '\0';
	  value = name + offset + 1;

	  add_alias (name, value);
	}
      else
	{
	  t = find_alias (name);
	  if (t)
	    print_alias (t);
	  else
	    {
	      builtin_error ("`%s' not found", name);
	      any_failed++;
	    }
	}
      list = list->next;
    }

  return (any_failed ? EXECUTION_FAILURE : EXECUTION_SUCCESS);
}
#endif /* ALIAS */

#line 141 "d:/jicamasdk/progs/bash-2.05/builtins/alias.def"

#if defined (ALIAS)
/* Remove aliases named in LIST from the aliases database. */
int
unalias_builtin (list)
     register WORD_LIST *list;
{
  register alias_t *alias;
  int opt, aflag;

  aflag = 0;
  reset_internal_getopt ();
  while ((opt = internal_getopt (list, "a")) != -1)
    {
      switch (opt)
	{
	case 'a':
	  aflag = 1;
	  break;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }

  list = loptend;

  if (aflag)
    {
      delete_all_aliases ();
      return (EXECUTION_SUCCESS);
    }

  aflag = 0;
  while (list)
    {
      alias = find_alias (list->word->word);

      if (alias)
	remove_alias (alias->name);
      else
	{
	  builtin_error ("`%s': not an alias", list->word->word);
	  aflag++;
	}

      list = list->next;
    }

  return (aflag ? EXECUTION_FAILURE : EXECUTION_SUCCESS);
}

/* Output ALIAS in such a way as to allow it to be read back in. */
static void
print_alias (alias)
     alias_t *alias;
{
  char *value;

  value = sh_single_quote (alias->value);
  printf ("alias %s=%s\n", alias->name, value);
  free (value);

  fflush (stdout);
}
#endif /* ALIAS */
