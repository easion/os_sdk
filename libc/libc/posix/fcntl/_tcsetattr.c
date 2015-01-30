/*
posix/_tcsetattr.c

Created:	June 11, 1993 by Philip Homburg
*/

#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>

int tcsetattr(fd, opt_actions, termios_p)
int fd;
int opt_actions;
const struct termios *termios_p;
{
  int request;


  switch(opt_actions)
  {
    case TCSANOW:	request = TCSETS;	break;
    case TCSADRAIN:	request = TCSETSW;	break;
    case TCSAFLUSH:	request = TCSETSF;	break;
    default:		errno = EINVAL;		return(-1);
  };

  return(ioctl(fd, request, (void *) termios_p));
}
