/* return.c, created from return.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/return.def"

#line 31 "d:/jicamasdk/progs/bash-2.05/builtins/return.def"

#include <config.h>

#if defined (HAVE_UNISTD_H)
#  ifdef _MINIX
#    include <sys/types.h>
#  endif
#  include <unistd.h>
#endif

#include "../shell.h"
#include "common.h"

extern int last_command_exit_value;
extern int subshell_environment;
extern int return_catch_flag, return_catch_value;

/* If we are executing a user-defined function then exit with the value
   specified as an argument.  if no argument is given, then the last
   exit status is used. */
int
return_builtin (list)
     WORD_LIST *list;
{
  return_catch_value = list ? get_exitstat (list) : last_command_exit_value;

  if (return_catch_flag)
    longjmp (return_catch, 1);
  else
    {
      builtin_error ("can only `return' from a function or sourced script");
      return (EXECUTION_FAILURE);
    }
}
