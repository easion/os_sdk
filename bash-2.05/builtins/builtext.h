/* builtext.h - The list of builtins found in libbuiltins.a. */
#if defined (ALIAS)
extern int alias_builtin __P((WORD_LIST *));
extern char *alias_doc[];
#endif /* ALIAS */
#if defined (ALIAS)
extern int unalias_builtin __P((WORD_LIST *));
extern char *unalias_doc[];
#endif /* ALIAS */
#if defined (READLINE)
extern int bind_builtin __P((WORD_LIST *));
extern char *bind_doc[];
#endif /* READLINE */
extern int break_builtin __P((WORD_LIST *));
extern char *break_doc[];
extern int continue_builtin __P((WORD_LIST *));
extern char *continue_doc[];
extern int builtin_builtin __P((WORD_LIST *));
extern char *builtin_doc[];
extern int cd_builtin __P((WORD_LIST *));
extern char *cd_doc[];
extern int pwd_builtin __P((WORD_LIST *));
extern char *pwd_doc[];
extern int colon_builtin __P((WORD_LIST *));
extern char *colon_builtin_doc[];
extern int colon_builtin __P((WORD_LIST *));
extern char *true_builtin_doc[];
extern int false_builtin __P((WORD_LIST *));
extern char *false_builtin_doc[];
extern int command_builtin __P((WORD_LIST *));
extern char *command_doc[];
extern int declare_builtin __P((WORD_LIST *));
extern char *declare_doc[];
extern int declare_builtin __P((WORD_LIST *));
extern char *typeset_doc[];
extern int local_builtin __P((WORD_LIST *));
extern char *local_doc[];
#if defined (V9_ECHO)
extern int echo_builtin __P((WORD_LIST *));
extern char *echo_doc[];
#endif /* V9_ECHO */
#if !defined (V9_ECHO)
extern int echo_builtin __P((WORD_LIST *));
extern char *echo_doc[];
#endif /* !V9_ECHO */
extern int enable_builtin __P((WORD_LIST *));
extern char *enable_doc[];
extern int eval_builtin __P((WORD_LIST *));
extern char *eval_doc[];
extern int getopts_builtin __P((WORD_LIST *));
extern char *getopts_doc[];
extern int exec_builtin __P((WORD_LIST *));
extern char *exec_doc[];
extern int exit_builtin __P((WORD_LIST *));
extern char *exit_doc[];
extern int logout_builtin __P((WORD_LIST *));
extern char *logout_doc[];
#if defined (HISTORY)
extern int fc_builtin __P((WORD_LIST *));
extern char *fc_doc[];
#endif /* HISTORY */
#if defined (JOB_CONTROL)
extern int fg_builtin __P((WORD_LIST *));
extern char *fg_doc[];
#endif /* JOB_CONTROL */
#if defined (JOB_CONTROL)
extern int bg_builtin __P((WORD_LIST *));
extern char *bg_doc[];
#endif /* JOB_CONTROL */
extern int hash_builtin __P((WORD_LIST *));
extern char *hash_doc[];
#if defined (HELP_BUILTIN)
extern int help_builtin __P((WORD_LIST *));
extern char *help_doc[];
#endif /* HELP_BUILTIN */
#if defined (HISTORY)
extern int history_builtin __P((WORD_LIST *));
extern char *history_doc[];
#endif /* HISTORY */
#if defined (JOB_CONTROL)
extern int jobs_builtin __P((WORD_LIST *));
extern char *jobs_doc[];
#endif /* JOB_CONTROL */
#if defined (JOB_CONTROL)
extern int disown_builtin __P((WORD_LIST *));
extern char *disown_doc[];
#endif /* JOB_CONTROL */
#if defined (JOB_CONTROL)
extern int kill_builtin __P((WORD_LIST *));
extern char *kill_doc[];
#endif /* JOB_CONTROL */
extern int let_builtin __P((WORD_LIST *));
extern char *let_doc[];
extern int read_builtin __P((WORD_LIST *));
extern char *read_doc[];
extern int return_builtin __P((WORD_LIST *));
extern char *return_doc[];
extern int set_builtin __P((WORD_LIST *));
extern char *set_doc[];
extern int unset_builtin __P((WORD_LIST *));
extern char *unset_doc[];
extern int export_builtin __P((WORD_LIST *));
extern char *export_doc[];
extern int readonly_builtin __P((WORD_LIST *));
extern char *readonly_doc[];
extern int shift_builtin __P((WORD_LIST *));
extern char *shift_doc[];
extern int source_builtin __P((WORD_LIST *));
extern char *source_doc[];
extern int source_builtin __P((WORD_LIST *));
extern char *dot_doc[];
#if defined (JOB_CONTROL)
extern int suspend_builtin __P((WORD_LIST *));
extern char *suspend_doc[];
#endif /* JOB_CONTROL */
extern int test_builtin __P((WORD_LIST *));
extern char *test_doc[];
extern int test_builtin __P((WORD_LIST *));
extern char *test_bracket_doc[];
extern int times_builtin __P((WORD_LIST *));
extern char *times_doc[];
extern int trap_builtin __P((WORD_LIST *));
extern char *trap_doc[];
extern int type_builtin __P((WORD_LIST *));
extern char *type_doc[];
#if !defined (_MINIX)
extern int ulimit_builtin __P((WORD_LIST *));
extern char *ulimit_doc[];
#endif /* !_MINIX */
extern int umask_builtin __P((WORD_LIST *));
extern char *umask_doc[];
#if defined (JOB_CONTROL)
extern int wait_builtin __P((WORD_LIST *));
extern char *wait_doc[];
#endif /* JOB_CONTROL */
#if !defined (JOB_CONTROL)
extern int wait_builtin __P((WORD_LIST *));
extern char *wait_doc[];
#endif /* !JOB_CONTROL */
extern char *for_doc[];
extern char *select_doc[];
extern char *time_doc[];
extern char *case_doc[];
extern char *if_doc[];
extern char *while_doc[];
extern char *until_doc[];
extern char *function_doc[];
extern char *grouping_braces_doc[];
extern char *fg_percent_doc[];
extern char *variable_help_doc[];
#if defined (PUSHD_AND_POPD)
extern int pushd_builtin __P((WORD_LIST *));
extern char *pushd_doc[];
#endif /* PUSHD_AND_POPD */
#if defined (PUSHD_AND_POPD)
extern int popd_builtin __P((WORD_LIST *));
extern char *popd_doc[];
#endif /* PUSHD_AND_POPD */
#if defined (PUSHD_AND_POPD)
extern int dirs_builtin __P((WORD_LIST *));
extern char *dirs_doc[];
#endif /* PUSHD_AND_POPD */
extern int shopt_builtin __P((WORD_LIST *));
extern char *shopt_builtin_doc[];
extern int printf_builtin __P((WORD_LIST *));
extern char *printf_doc[];
#if defined (PROGRAMMABLE_COMPLETION)
extern int complete_builtin __P((WORD_LIST *));
extern char *complete_doc[];
#endif /* PROGRAMMABLE_COMPLETION */
#if defined (PROGRAMMABLE_COMPLETION)
extern int compgen_builtin __P((WORD_LIST *));
extern char *compgen_doc[];
#endif /* PROGRAMMABLE_COMPLETION */
