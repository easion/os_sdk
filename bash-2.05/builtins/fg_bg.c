/* fg_bg.c, created from fg_bg.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/fg_bg.def"

#line 32 "d:/jicamasdk/progs/bash-2.05/builtins/fg_bg.def"

#include <config.h>

#include "../bashtypes.h"
#include <signal.h>

#if defined (HAVE_UNISTD_H)
#  include <unistd.h>
#endif

#include "../shell.h"
#include "../jobs.h"
#include "common.h"

#if defined (JOB_CONTROL)
extern char *this_command_name;

static int fg_bg __P((WORD_LIST *, int));

/* How to bring a job into the foreground. */
int
fg_builtin (list)
     WORD_LIST *list;
{
  int fg_bit;
  register WORD_LIST *t;

  if (job_control == 0)
    {
      builtin_error ("no job control");
      return (EXECUTION_FAILURE);
    }

  if (no_options (list))
    return (EX_USAGE);

  /* If the last arg on the line is '&', then start this job in the
     background.  Else, fg the job. */
  for (t = list; t && t->next; t = t->next)
    ;
  fg_bit = (t && t->word->word[0] == '&' && t->word->word[1] == '\0') == 0;

  return (fg_bg (list, fg_bit));
}
#endif /* JOB_CONTROL */

#line 86 "d:/jicamasdk/progs/bash-2.05/builtins/fg_bg.def"

#if defined (JOB_CONTROL)
/* How to put a job into the background. */
int
bg_builtin (list)
     WORD_LIST *list;
{
  if (job_control == 0)
    {
      builtin_error ("no job control");
      return (EXECUTION_FAILURE);
    }

  if (no_options (list))
    return (EX_USAGE);

  return (fg_bg (list, 0));
}

/* How to put a job into the foreground/background. */
static int
fg_bg (list, foreground)
     WORD_LIST *list;
     int foreground;
{
  sigset_t set, oset;
  int job, status, old_async_pid;

  BLOCK_CHILD (set, oset);
  job = get_job_spec (list);

  if (job < 0 || job >= job_slots || jobs[job] == 0)
    {
      if (job != DUP_JOB)
	builtin_error ("%s: no such job", list ? list->word->word : "current");

      goto failure;
    }

  /* Or if jobs[job]->pgrp == shell_pgrp. */
  if (IS_JOBCONTROL (job) == 0)
    {
      builtin_error ("job %%%d started without job control", job + 1);
      goto failure;
    }

  if (foreground == 0)
    {
      old_async_pid = last_asynchronous_pid;
      last_asynchronous_pid = jobs[job]->pgrp;	/* As per Posix.2 5.4.2 */
    }

  status = start_job (job, foreground);

  if (status >= 0)
    {
    /* win: */
      UNBLOCK_CHILD (oset);
      return (status);
    }
  else
    {
      if (foreground == 0)
	last_asynchronous_pid = old_async_pid;

    failure:
      UNBLOCK_CHILD (oset);
      return (EXECUTION_FAILURE);
    }
}
#endif /* JOB_CONTROL */
