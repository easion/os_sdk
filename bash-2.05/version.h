/* Version control for the shell.  This file gets changed when you say
   `make version.h' to the Makefile.  It is created by mkversion. */

/* The distribution version number of this shell. */
#define DISTVERSION "2.05a"

/* The last built version of this shell. */
#define BUILDVERSION 13

/* The release status of this shell. */
#define RELSTATUS "release"

/* A version string for use by sccs and the what command. */
#define SCCSVERSION "@(#)Bash version 2.05a.0(13) release GNU"

/* Functions from version.c. */
extern char *shell_version_string __P((void));
extern void show_shell_version __P((int));
