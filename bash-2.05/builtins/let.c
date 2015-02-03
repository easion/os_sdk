/* let.c, created from let.def. */
#line 62 "d:/jicamasdk/progs/bash-2.05/builtins/let.def"

#include <config.h>

#if defined (HAVE_UNISTD_H)
#  ifdef _MINIX
#    include <sys/types.h>
#  endif
#  include <unistd.h>
#endif

#include "../shell.h"
#include "common.h"

/* Arithmetic LET function. */
int
let_builtin (list)
     WORD_LIST *list;
{
  long ret;
  int expok;

  if (list == 0)
    {
      builtin_error ("expression expected");
      return (EXECUTION_FAILURE);
    }

  for (; list; list = list->next)
    {
      ret = evalexp (list->word->word, &expok);
      if (expok == 0)
	return (EXECUTION_FAILURE);
    }

  return ((ret == 0) ? EXECUTION_FAILURE : EXECUTION_SUCCESS);
}

#ifdef INCLUDE_UNUSED
int
exp_builtin (list)
     WORD_LIST *list;
{
  char *exp;
  int ret, expok;

  if (list == 0)
    {
      builtin_error ("expression expected");
      return (EXECUTION_FAILURE);
    }

  exp = string_list (list);
  ret = evalexp (exp, &expok);
  (void)free (exp);
  return (((ret == 0) || (expok == 0)) ? EXECUTION_FAILURE : EXECUTION_SUCCESS);
}
#endif
