/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_mntent_h_
#define __dj_include_mntent_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define	MNT_MNTTAB	"/rd/1/mnttab.ini"

struct mntent
{
  char *mnt_fsname;
  char *mnt_dir;
  char *mnt_type;
  char *mnt_opts;
  int  mnt_freq;
  int  mnt_passno;
  long mnt_time;
};

extern FILE		* setmntent(char *,char *);
extern struct mntent	* getmntent(FILE *);
extern int		  addmntent(FILE *,struct mntent *);
extern char		* hasmntopt(struct mntent *,char *);
extern int		  endmntent(FILE *);

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_mntent_h_ */
