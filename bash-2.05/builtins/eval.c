/* eval.c, created from eval.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/eval.def"

#line 29 "d:/jicamasdk/progs/bash-2.05/builtins/eval.def"

#include <config.h>
#if defined (HAVE_UNISTD_H)
#  ifdef _MINIX
#    include <sys/types.h>
#  endif
#  include <unistd.h>
#endif

#include "../shell.h"
#include "bashgetopt.h"
#include "common.h"

/* Parse the string that these words make, and execute the command found. */
int
eval_builtin (list)
     WORD_LIST *list;
{
  if (no_options (list))
    return (EX_USAGE);

  /* Note that parse_and_execute () frees the string it is passed. */
  return (list ? parse_and_execute (string_list (list), "eval", SEVAL_NOHIST) : EXECUTION_SUCCESS);
}
