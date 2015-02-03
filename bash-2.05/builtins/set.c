/* set.c, created from set.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/set.def"

#include <config.h>

#if defined (HAVE_UNISTD_H)
#  ifdef _MINIX
#    include <sys/types.h>
#  endif
#  include <unistd.h>
#endif

#include <stdio.h>

#include "../bashansi.h"

#include "../shell.h"
#include "../flags.h"
#include "common.h"
#include "bashgetopt.h"

#if defined (READLINE)
#  include "../input.h"
#  include "../bashline.h"
#  include <readline/readline.h>
#endif

#if defined (HISTORY)
#  include "../bashhist.h"
#endif

extern int noclobber, posixly_correct, ignoreeof, eof_encountered_limit;
#if defined (HISTORY)
extern int dont_save_function_defs;
#endif
#if defined (READLINE)
extern int no_line_editing;
#endif /* READLINE */

#line 137 "d:/jicamasdk/progs/bash-2.05/builtins/set.def"

static void print_minus_o_option __P((char *, int, int));
static void print_all_shell_variables __P((void));

static int set_ignoreeof __P((int, char *));
static int set_posix_mode __P((int, char *));

#if defined (READLINE)
static int set_edit_mode __P((int, char *));
static int get_edit_mode __P((char *));
#endif

#if defined (HISTORY)
static int bash_set_history __P((int, char *));
#endif

static char *on = "on";
static char *off = "off";

/* An a-list used to match long options for set -o to the corresponding
   option letter. */
struct {
  char *name;
  int letter;
} o_options[] = {
  { "allexport",  'a' },
#if defined (BRACE_EXPANSION)
  { "braceexpand",'B' },
#endif
  { "errexit",	  'e' },
  { "hashall",    'h' },
#if defined (BANG_HISTORY)
  { "histexpand", 'H' },
#endif /* BANG_HISTORY */
  { "keyword",    'k' },
  { "monitor",	  'm' },
  { "noclobber",  'C' },
  { "noexec",	  'n' },
  { "noglob",	  'f' },
#if defined (JOB_CONTROL)
  { "notify",	  'b' },
#endif /* JOB_CONTROL */
  { "nounset",	  'u' },
  { "onecmd",	  't' },
  { "physical",   'P' },
  { "privileged", 'p' },
  { "verbose",	  'v' },
  { "xtrace",	  'x' },
  {(char *)NULL, 0 },
};

typedef int setopt_set_func_t __P((int, char *));
typedef int setopt_get_func_t __P((char *));

struct {
  char *name;
  int *variable;
  setopt_set_func_t *set_func;
  setopt_get_func_t *get_func;
} binary_o_options[] = {
#if defined (HISTORY)
  { "history", &remember_on_history, bash_set_history, (setopt_get_func_t *)NULL },
#endif
  { "ignoreeof", &ignoreeof, set_ignoreeof, (setopt_get_func_t *)NULL },
  { "interactive-comments", &interactive_comments, (setopt_set_func_t *)NULL, (setopt_get_func_t *)NULL },
#if defined (HISTORY)
  { "nolog", &dont_save_function_defs, (setopt_set_func_t *)NULL, (setopt_get_func_t *)NULL },
#endif
  { "posix", &posixly_correct, set_posix_mode, (setopt_get_func_t *)NULL },
#if defined (READLINE)
  { "emacs", (int *)NULL, set_edit_mode, get_edit_mode },
  { "vi", (int *)NULL, set_edit_mode, get_edit_mode },
#endif
  { (char *)NULL, (int *)NULL, (setopt_set_func_t *)NULL, (setopt_get_func_t *)NULL }
};

#define GET_BINARY_O_OPTION_VALUE(i, name) \
  ((binary_o_options[i].get_func) ? (*binary_o_options[i].get_func) (name) \
				  : (*binary_o_options[i].variable))

#define SET_BINARY_O_OPTION_VALUE(i, onoff, name) \
  ((binary_o_options[i].set_func) ? (*binary_o_options[i].set_func) (onoff, name) \
				  : (*binary_o_options[i].variable = (onoff == FLAG_ON)))

int
minus_o_option_value (name)
     char *name;
{
  register int	i;
  int *on_or_off;

  for (i = 0; o_options[i].name; i++)
    {
      if (STREQ (name, o_options[i].name))
	{
	  on_or_off = find_flag (o_options[i].letter);
	  return ((on_or_off == FLAG_UNKNOWN) ? -1 : *on_or_off);
	}
    }
  for (i = 0; binary_o_options[i].name; i++)
    {
      if (STREQ (name, binary_o_options[i].name))
	return (GET_BINARY_O_OPTION_VALUE (i, name));
    }

  return (-1);
}

#define MINUS_O_FORMAT "%-15s\t%s\n"

static void
print_minus_o_option (name, value, pflag)
     char *name;
     int value, pflag;
{
  if (pflag == 0)
    printf (MINUS_O_FORMAT, name, value ? on : off);
  else
    printf ("set %co %s\n", value ? '-' : '+', name);
}

void
list_minus_o_opts (mode, reusable)
     int mode, reusable;
{
  register int	i;
  int *on_or_off, value;

  for (value = i = 0; o_options[i].name; i++)
    {
      on_or_off = find_flag (o_options[i].letter);
      if (on_or_off == FLAG_UNKNOWN)
	on_or_off = &value;
      if (mode == -1 || mode == *on_or_off)
	print_minus_o_option (o_options[i].name, *on_or_off, reusable);
    }
  for (i = 0; binary_o_options[i].name; i++)
    {
      value = GET_BINARY_O_OPTION_VALUE (i, binary_o_options[i].name);
      if (mode == -1 || mode == value)
	print_minus_o_option (binary_o_options[i].name, value, reusable);
    }
}

char **
get_minus_o_opts ()
{
  char **ret;
  int n, i, ind;

  n = (sizeof (o_options) / sizeof (o_options[0])) +
      (sizeof (binary_o_options) / sizeof (binary_o_options[0]));
  ret = alloc_array (n + 1);
  for (i = ind = 0; o_options[i].name; i++)
    ret[ind++] = o_options[i].name;
  for (i = 0; binary_o_options[i].name; i++)
    ret[ind++] = binary_o_options[i].name;
  ret[ind] = (char *)NULL;
  return ret;
}

static int
set_ignoreeof (on_or_off, option_name)
     int on_or_off;
     char *option_name;
{
  ignoreeof = on_or_off == FLAG_ON;
  unbind_variable ("ignoreeof");
  if (ignoreeof)
    bind_variable ("IGNOREEOF", "10"); 
  else
    unbind_variable ("IGNOREEOF");
  sv_ignoreeof ("IGNOREEOF");
  return 0;
}

static int
set_posix_mode (on_or_off, option_name)
     int on_or_off;
     char *option_name;
{
  posixly_correct = on_or_off == FLAG_ON;
  if (posixly_correct == 0)
    unbind_variable ("POSIXLY_CORRECT");
  else
    bind_variable ("POSIXLY_CORRECT", "y");
  sv_strict_posix ("POSIXLY_CORRECT");
  return (0);
}

#if defined (READLINE)
/* Magic.  This code `knows' how readline handles rl_editing_mode. */
static int
set_edit_mode (on_or_off, option_name)
     int on_or_off;
     char *option_name;
{
  int isemacs;

  if (on_or_off == FLAG_ON)
    {
      rl_variable_bind ("editing-mode", option_name);

      if (interactive)
	with_input_from_stdin ();
      no_line_editing = 0;
    }
  else
    {
      isemacs = rl_editing_mode == 1;
      if ((isemacs && *option_name == 'e') || (!isemacs && *option_name == 'v'))
	{
	  if (interactive)
	    with_input_from_stream (stdin, "stdin");
	  no_line_editing = 1;
	}
    }
  return 1-no_line_editing;
}

static int
get_edit_mode (name)
     char *name;
{
  return (*name == 'e' ? no_line_editing == 0 && rl_editing_mode == 1
		       : no_line_editing == 0 && rl_editing_mode == 0);
}
#endif /* READLINE */

#if defined (HISTORY)
static int
bash_set_history (on_or_off, option_name)
     int on_or_off;
     char *option_name;
{
  if (on_or_off == FLAG_ON)
    {
      bash_history_enable ();
      if (history_lines_this_session == 0)
	load_history ();
    }
  else
    bash_history_disable ();
  return (1 - remember_on_history);
}
#endif

int
set_minus_o_option (on_or_off, option_name)
     int on_or_off;
     char *option_name;
{
  int option_char;
  register int i;

  for (i = 0; binary_o_options[i].name; i++)
    {
      if (STREQ (option_name, binary_o_options[i].name))
	{
	  SET_BINARY_O_OPTION_VALUE (i, on_or_off, option_name);
	  return (EXECUTION_SUCCESS);
	}
    }

  for (i = 0, option_char = -1; o_options[i].name; i++)
    {
      if (STREQ (option_name, o_options[i].name))
	{
	  option_char = o_options[i].letter;
	  break;
	}
    }
  if (option_char == -1)
    {
      builtin_error ("%s: unknown option name", option_name);
      return (EXECUTION_FAILURE);
    }
 if (change_flag (option_char, on_or_off) == FLAG_ERROR)
    {
      bad_option (option_name);
      return (EXECUTION_FAILURE);
    }
  return (EXECUTION_SUCCESS);
}

static void
print_all_shell_variables ()
{
  SHELL_VAR **vars;

  vars = all_shell_variables ();
  if (vars)
    {
      print_var_list (vars);
      free (vars);
    }

  /* POSIX.2 does not allow function names and definitions to be output when
     `set' is invoked without options (PASC Interp #202). */
  if (posixly_correct == 0)
    {
      vars = all_shell_functions ();
      if (vars)
	{
	  print_func_list (vars);
	  free (vars);
	}
    }
}

void
set_shellopts ()
{
  char *value;
  int vsize, i, vptr, *ip, exported;
  SHELL_VAR *v;

  for (vsize = i = 0; o_options[i].name; i++)
    {
      ip = find_flag (o_options[i].letter);
      if (ip && *ip)
	vsize += strlen (o_options[i].name) + 1;
    }
  for (i = 0; binary_o_options[i].name; i++)
    if (GET_BINARY_O_OPTION_VALUE (i, binary_o_options[i].name))
      vsize += strlen (binary_o_options[i].name) + 1;

  value = (char *)xmalloc (vsize + 1);

  for (i = vptr = 0; o_options[i].name; i++)
    {
      ip = find_flag (o_options[i].letter);
      if (ip && *ip)
	{
	  strcpy (value + vptr, o_options[i].name);
	  vptr += strlen (o_options[i].name);
	  value[vptr++] = ':';
	}
    }
  for (i = 0; binary_o_options[i].name; i++)
    if (GET_BINARY_O_OPTION_VALUE (i, binary_o_options[i].name))
      {
	strcpy (value + vptr, binary_o_options[i].name);
	vptr += strlen (binary_o_options[i].name);
	value[vptr++] = ':';
      }
  if (vptr)
    vptr--;			/* cut off trailing colon */
  value[vptr] = '\0';

  v = find_variable ("SHELLOPTS");

  /* Turn off the read-only attribute so we can bind the new value, and
     note whether or not the variable was exported. */
  if (v)
    {
      VUNSETATTR (v, att_readonly);
      exported = exported_p (v);
    }
  else
    exported = 0;

  v = bind_variable ("SHELLOPTS", value);

  /* Turn the read-only attribute back on, and turn off the export attribute
     if it was set implicitly by mark_modified_vars and SHELLOPTS was not
     exported before we bound the new value. */
  VSETATTR (v, att_readonly);
  if (mark_modified_vars && exported == 0 && exported_p (v))
    VUNSETATTR (v, att_exported);

  free (value);
}

void
parse_shellopts (value)
     char *value;
{
  char *vname;
  int vptr;

  vptr = 0;
  while (vname = extract_colon_unit (value, &vptr))
    {
      set_minus_o_option (FLAG_ON, vname);
      free (vname);
    }
}

void
initialize_shell_options (no_shellopts)
     int no_shellopts;
{
  char *temp;
  SHELL_VAR *var;

  if (no_shellopts == 0)
    {
      var = find_variable ("SHELLOPTS");
      /* set up any shell options we may have inherited. */
      if (var && imported_p (var))
	{
	  temp = (array_p (var)) ? (char *)NULL : savestring (value_cell (var));
	  if (temp)
	    {
	      parse_shellopts (temp);
	      free (temp);
	    }
	}
    }

  /* Set up the $SHELLOPTS variable. */
  set_shellopts ();
}

/* Reset the values of the -o options that are not also shell flags.  This is
   called from execute_cmd.c:initialize_subshell() when setting up a subshell
   to run an executable shell script without a leading `#!'. */
void
reset_shell_options ()
{
#if defined (HISTORY)
  remember_on_history = 1;
#endif
  ignoreeof = 0;
}

/* Set some flags from the word values in the input list.  If LIST is empty,
   then print out the values of the variables instead.  If LIST contains
   non-flags, then set $1 - $9 to the successive words of LIST. */
int
set_builtin (list)
     WORD_LIST *list;
{
  int on_or_off, flag_name, force_assignment, opts_changed;
  WORD_LIST *l;
  register char *arg;

  if (list == 0)
    {
      print_all_shell_variables ();
      return (EXECUTION_SUCCESS);
    }

  /* Check validity of flag arguments. */
  if (*list->word->word == '-' || *list->word->word == '+')
    {
      for (l = list; l && (arg = l->word->word); l = l->next)
	{
	  char c;

	  if (arg[0] != '-' && arg[0] != '+')
	    break;

	  /* `-' or `--' signifies end of flag arguments. */
	  if (arg[0] == '-' && (!arg[1] || (arg[1] == '-' && !arg[2])))
	    break;

	  while (c = *++arg)
	    {
	      if (find_flag (c) == FLAG_UNKNOWN && c != 'o')
		{
		  char s[2];
		  s[0] = c; s[1] = '\0';
		  bad_option (s);
		  if (c == '?')
		    builtin_usage ();
		  return (c == '?' ? EXECUTION_SUCCESS : EXECUTION_FAILURE);
		}
	    }
	}
    }

  /* Do the set command.  While the list consists of words starting with
     '-' or '+' treat them as flags, otherwise, start assigning them to
     $1 ... $n. */
  for (force_assignment = opts_changed = 0; list; )
    {
      arg = list->word->word;

      /* If the argument is `--' or `-' then signal the end of the list
	 and remember the remaining arguments. */
      if (arg[0] == '-' && (!arg[1] || (arg[1] == '-' && !arg[2])))
	{
	  list = list->next;

	  /* `set --' unsets the positional parameters. */
	  if (arg[1] == '-')
	    force_assignment = 1;

	  /* Until told differently, the old shell behaviour of
	     `set - [arg ...]' being equivalent to `set +xv [arg ...]'
	     stands.  Posix.2 says the behaviour is marked as obsolescent. */
	  else
	    {
	      change_flag ('x', '+');
	      change_flag ('v', '+');
	      opts_changed = 1;
	    }

	  break;
	}

      if ((on_or_off = *arg) && (on_or_off == '-' || on_or_off == '+'))
	{
	  while (flag_name = *++arg)
	    {
	      if (flag_name == '?')
		{
		  builtin_usage ();
		  return (EXECUTION_SUCCESS);
		}
	      else if (flag_name == 'o') /* -+o option-name */
		{
		  char *option_name;
		  WORD_LIST *opt;

		  opt = list->next;

		  if (opt == 0)
		    {
		      list_minus_o_opts (-1, (on_or_off == '+'));
		      continue;
		    }

		  option_name = opt->word->word;

		  if (option_name == 0 || *option_name == '\0' ||
		      *option_name == '-' || *option_name == '+')
		    {
		      list_minus_o_opts (-1, (on_or_off == '+'));
		      continue;
		    }
		  list = list->next; /* Skip over option name. */

		  opts_changed = 1;
		  if (set_minus_o_option (on_or_off, option_name) != EXECUTION_SUCCESS)
		    {
		      set_shellopts ();
		      return (EXECUTION_FAILURE);
		    }
		}
	      else if (change_flag (flag_name, on_or_off) == FLAG_ERROR)
		{
		  char opt[3];
		  opt[0] = on_or_off;
		  opt[1] = flag_name;
		  opt[2] = '\0';
		  bad_option (opt);
		  builtin_usage ();
		  set_shellopts ();
		  return (EXECUTION_FAILURE);
		}
	      opts_changed = 1;
	    }
	}
      else
	{
	  break;
	}
      list = list->next;
    }

  /* Assigning $1 ... $n */
  if (list || force_assignment)
    remember_args (list, 1);
  /* Set up new value of $SHELLOPTS */
  if (opts_changed)
    set_shellopts ();
  return (EXECUTION_SUCCESS);
}

#line 718 "d:/jicamasdk/progs/bash-2.05/builtins/set.def"

#define NEXT_VARIABLE()	any_failed++; list = list->next; continue;

int
unset_builtin (list)
  WORD_LIST *list;
{
  int unset_function, unset_variable, unset_array, opt, any_failed;
  char *name;

  unset_function = unset_variable = unset_array = any_failed = 0;

  reset_internal_getopt ();
  while ((opt = internal_getopt (list, "fv")) != -1)
    {
      switch (opt)
	{
	case 'f':
	  unset_function = 1;
	  break;
	case 'v':
	  unset_variable = 1;
	  break;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }

  list = loptend;

  if (unset_function && unset_variable)
    {
      builtin_error ("cannot simultaneously unset a function and a variable");
      return (EXECUTION_FAILURE);
    }

  while (list)
    {
      SHELL_VAR *var;
      int tem;
#if defined (ARRAY_VARS)
      char *t;
#endif

      name = list->word->word;

#if defined (ARRAY_VARS)
      unset_array = 0;
      if (!unset_function && valid_array_reference (name))
	{
	  t = strchr (name, '[');
	  *t++ = '\0';
	  unset_array++;
	}
#endif

      /* Bash allows functions with names which are not valid identifiers
	 to be created when not in posix mode, so check only when in posix
	 mode when unsetting a function. */
      if (((unset_function && posixly_correct) || !unset_function) && legal_identifier (name) == 0)
	{
	  builtin_error ("`%s': not a valid identifier", name);
	  NEXT_VARIABLE ();
	}

      var = unset_function ? find_function (name) : find_variable (name);

      if (var && !unset_function && non_unsettable_p (var))
	{
	  builtin_error ("%s: cannot unset", name);
	  NEXT_VARIABLE ();
	}

      /* Posix.2 says that unsetting readonly variables is an error. */
      if (var && readonly_p (var))
	{
	  builtin_error ("%s: cannot unset: readonly %s",
			 name, unset_function ? "function" : "variable");
	  NEXT_VARIABLE ();
	}

      /* Unless the -f option is supplied, the name refers to a variable. */
#if defined (ARRAY_VARS)
      if (var && unset_array)
	{
	  if (array_p (var) == 0)
	    {
	      builtin_error ("%s: not an array variable", name);
	      NEXT_VARIABLE ();
	    }
	  else
	    tem = unbind_array_element (var, t);
	}
      else
#endif /* ARRAY_VARS */
      tem = makunbound (name, unset_function ? shell_functions : shell_variables);

      /* This is what Posix.2 draft 11+ says.  ``If neither -f nor -v
	 is specified, the name refers to a variable; if a variable by
	 that name does not exist, a function by that name, if any,
	 shall be unset.'' */
      if (tem == -1 && !unset_function && !unset_variable)
	tem = makunbound (name, shell_functions);

      if (tem == -1)
	any_failed++;
      else if (!unset_function)
	stupidly_hack_special_variables (name);

      list = list->next;
    }

  return (any_failed ? EXECUTION_FAILURE : EXECUTION_SUCCESS);
}
