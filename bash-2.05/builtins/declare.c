/* declare.c, created from declare.def. */
#line 23 "d:/jicamasdk/progs/bash-2.05/builtins/declare.def"

#line 50 "d:/jicamasdk/progs/bash-2.05/builtins/declare.def"

#line 56 "d:/jicamasdk/progs/bash-2.05/builtins/declare.def"

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
#include "common.h"
#include "builtext.h"

extern int array_needs_making;

static int declare_internal __P((register WORD_LIST *, int));

/* Declare or change variable attributes. */
int
declare_builtin (list)
     register WORD_LIST *list;
{
  return (declare_internal (list, 0));
}

#line 93 "d:/jicamasdk/progs/bash-2.05/builtins/declare.def"
int
local_builtin (list)
     register WORD_LIST *list;
{
  if (variable_context)
    return (declare_internal (list, 1));
  else
    {
      builtin_error ("can only be used in a function");
      return (EXECUTION_FAILURE);
    }
}

/* The workhorse function. */
static int
declare_internal (list, local_var)
     register WORD_LIST *list;
     int local_var;
{
  int flags_on, flags_off, *flags, any_failed, assign_error, pflag, nodefs;
  char *t, *subscript_start;
  SHELL_VAR *var;

  flags_on = flags_off = any_failed = assign_error = pflag = nodefs = 0;
  while (list)
    {
      t = list->word->word;
      if (t[0] == '-' && t[1] == '-' && t[2] == '\0')
	{
	  list = list->next;
	  break;
	}

      if (*t != '+' && *t != '-')
	break;

      flags = (*t++ == '+') ? &flags_off : &flags_on;

      while (*t)
	{
	  if (*t == 'p' && local_var == 0)
	    pflag++, t++;
	  else if (*t == 'F')
	    {
	      nodefs++;
	      *flags |= att_function; t++;
	    }
	  else if (*t == 'f')
	    *flags |= att_function, t++;
	  else if (*t == 'x')
	    *flags |= att_exported, t++, array_needs_making = 1;
	  else if (*t == 'r')
	    *flags |= att_readonly, t++;
	  else if (*t == 'i')
	    *flags |= att_integer, t++;
#if defined (ARRAY_VARS)
	  else if (*t == 'a')
	    *flags |= att_array, t++;
#endif
	  else
	    {
	      builtin_error ("unknown option: `-%c'", *t);
	      builtin_usage ();
	      return (EX_USAGE);
	    }
	}

      list = list->next;
    }

  /* If there are no more arguments left, then we just want to show
     some variables. */
  if (list == 0)	/* declare -[afFirx] */
    {
      /* Show local variables defined at this context level if this is
	 the `local' builtin. */
      if (local_var)
	{
	  register SHELL_VAR **vlist;
	  register int i;

	  vlist = map_over (variable_in_context, shell_variables);

	  if (vlist)
	    {
	      for (i = 0; vlist[i]; i++)
		print_assignment (vlist[i]);

	      free (vlist);
	    }
	}
      else
	{
	  if (flags_on == 0)
	    set_builtin ((WORD_LIST *)NULL);
	  else
	    set_or_show_attributes ((WORD_LIST *)NULL, flags_on, nodefs);
	}

      fflush (stdout);
      return (EXECUTION_SUCCESS);
    }

  if (pflag)	/* declare -p [-afFirx] name [name...] */
    {
      for (any_failed = 0; list; list = list->next)
	{
	  pflag = show_name_attributes (list->word->word, nodefs);
	  if (pflag)
	    {
	      builtin_error ("%s: not found", list->word->word);
	      any_failed++;
	    }
	}
      return (any_failed ? EXECUTION_FAILURE : EXECUTION_SUCCESS);
    }

#define NEXT_VARIABLE() free (name); list = list->next; continue

  /* There are arguments left, so we are making variables. */
  while (list)		/* declare [-afFirx] name [name ...] */
    {
      char *value, *name;
      int offset;
#if defined (ARRAY_VARS)
      int making_array_special, compound_array_assign, simple_array_assign;
#endif

      name = savestring (list->word->word);
      offset = assignment (name);

      if (offset)	/* declare [-afFirx] name=value */
	{
	  name[offset] = '\0';
	  value = name + offset + 1;
	}
      else
	value = "";

#if defined (ARRAY_VARS)
      compound_array_assign = simple_array_assign = 0;
      subscript_start = (char *)NULL;
      if (t = strchr (name, '['))	/* ] */
	{
	  subscript_start = t;
	  *t = '\0';
	  making_array_special = 1;
	}
      else
	making_array_special = 0;
#endif
	
      if (legal_identifier (name) == 0)
	{
	  builtin_error ("`%s': not a valid identifier", name);
	  assign_error++;
	  NEXT_VARIABLE ();
	}

      /* If VARIABLE_CONTEXT has a non-zero value, then we are executing
	 inside of a function.  This means we should make local variables,
	 not global ones. */

      if (variable_context)
	{
#if defined (ARRAY_VARS)
	  if ((flags_on & att_array) || making_array_special)
	    var = make_local_array_variable (name);
	  else
#endif
	  var = make_local_variable (name);
	  if (var == 0)
	    {
	      any_failed++;
	      NEXT_VARIABLE ();
	    }
	}

      /* If we are declaring a function, then complain about it in some way.
	 We don't let people make functions by saying `typeset -f foo=bar'. */

      /* There should be a way, however, to let people look at a particular
	 function definition by saying `typeset -f foo'. */

      if (flags_on & att_function)
	{
	  if (offset)	/* declare -f [-rix] foo=bar */
	    {
	      builtin_error ("cannot use `-f' to make functions");
	      free (name);
	      return (EXECUTION_FAILURE);
	    }
	  else		/* declare -f [-rx] name [name...] */
	    {
	      var = find_function (name);

	      if (var)
		{
		  if (readonly_p (var) && (flags_off & att_readonly))
		    {
		      builtin_error ("%s: readonly function", name);
		      any_failed++;
		      NEXT_VARIABLE ();
		    }

		  /* declare -[Ff] name [name...] */
		  if (flags_on == att_function && flags_off == 0)
		    {
		      t = nodefs ? var->name
				 : named_function_string (name, function_cell (var), 1);
		      printf ("%s\n", t);
		    }
		  else		/* declare -[fF] -[rx] name [name...] */
		    {
		      VSETATTR (var, flags_on);
		      VUNSETATTR (var, flags_off);
		    }
		}
	      else
		any_failed++;
	      NEXT_VARIABLE ();
	    }
	}
      else		/* declare -[airx] name [name...] */
	{
	  var = find_variable (name);

	  if (var == 0)
	    {
#if defined (ARRAY_VARS)
	      if ((flags_on & att_array) || making_array_special)
		var = make_new_array_variable (name);
	      else
#endif
	      var = bind_variable (name, "");
	    }

	  /* Cannot use declare +r to turn off readonly attribute. */ 
	  if (readonly_p (var) && (flags_off & att_readonly))
	    {
	      builtin_error ("%s: readonly variable", name);
	      any_failed++;
	      NEXT_VARIABLE ();
	    }

	  /* Cannot use declare to assign value to readonly or noassign
	     variable. */
	  if ((readonly_p (var) || noassign_p (var)) && offset)
	    {
	      if (readonly_p (var))
		builtin_error ("%s: readonly variable", name);
	      assign_error++;
	      NEXT_VARIABLE ();
	    }

#if defined (ARRAY_VARS)
	  if ((making_array_special || (flags_on & att_array) || array_p (var)) && offset)
	    {
	      if (value[0] == '(' && strchr (value, ')'))
		compound_array_assign = 1;
	      else
		simple_array_assign = 1;
	    }

	  /* Cannot use declare +a name to remove an array variable. */
	  if ((flags_off & att_array) && array_p (var))
	    {
	      builtin_error ("%s: cannot destroy array variables in this way", name);
	      any_failed++;
	      NEXT_VARIABLE ();
	    }

	  /* declare -a name makes name an array variable. */
	  if ((making_array_special || (flags_on & att_array)) && array_p (var) == 0)
	    var = convert_var_to_array (var);
#endif /* ARRAY_VARS */

	  VSETATTR (var, flags_on);
	  VUNSETATTR (var, flags_off);

#if defined (ARRAY_VARS)
	  if (offset && compound_array_assign)
	    assign_array_var_from_string (var, value);
	  else if (simple_array_assign && subscript_start)
	    {
	      /* declare [-a] name[N]=value */
	      *subscript_start = '[';	/* ] */
	      var = assign_array_element (name, value);
	      *subscript_start = '\0';
	    }
	  else if (simple_array_assign)
	    /* let bind_array_variable take care of this. */
	    bind_array_variable (name, 0, value);
	  else
#endif
	  /* bind_variable_value duplicates the essential internals of
	     bind_variable() */
	  if (offset)
	    bind_variable_value (var, value);

	  /* If we found this variable in the temporary environment, as with
	     `var=value declare -x var', make sure it is treated identically
	     to `var=value export var'.  Do the same for `declare -r' and
	     `readonly'.  Preserve the attributes, except for att_tempvar. */
	  if ((flags_on & (att_exported|att_readonly)) && tempvar_p (var))
	    {
	      SHELL_VAR *tv;
	      tv = bind_variable (var->name, var->value ? var->value : "");
	      tv->attributes = var->attributes & ~att_tempvar;
	      dispose_variable (var);
	    }
	}

      stupidly_hack_special_variables (name);

      NEXT_VARIABLE ();
    }

  return (assign_error ? EX_BADASSIGN
		       : ((any_failed == 0) ? EXECUTION_SUCCESS
  					    : EXECUTION_FAILURE));
}
