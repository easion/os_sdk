/* builtin.c, created from builtin.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/builtin.def"

#line 31 "d:/jicamasdk/progs/bash-2.05/builtins/builtin.def"
#include <config.h>

#if defined (HAVE_UNISTD_H)
#  ifdef _MINIX
#    include <sys/types.h>
#  endif
#  include <unistd.h>
#endif

#include "../shell.h"
#include "common.h"

extern char *this_command_name;

/* Run the command mentioned in list directly, without going through the
   normal alias/function/builtin/filename lookup process. */
int
builtin_builtin (list)
     WORD_LIST *list;
{
  sh_builtin_func_t *function;
  register char *command;

  if (!list)
    return (EXECUTION_SUCCESS);

  command = (list->word->word);
#if defined (DISABLED_BUILTINS)
  function = builtin_address (command);
#else /* !DISABLED_BUILTINS */
  function = find_shell_builtin (command);
#endif /* !DISABLED_BUILTINS */

  if (!function)
    {
      builtin_error ("%s: not a shell builtin", command);
      return (EXECUTION_FAILURE);
    }
  else
    {
      this_command_name = command;
      list = list->next;
      return ((*function) (list));
    }
}
