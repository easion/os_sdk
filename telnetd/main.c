/*
 * TNET		A server program for MINIX which implements the TCP/IP
 *		suite of networking protocols.  It is based on the
 *		TCP/IP code written by Phil Karn et al, as found in
 *		his NET package for Packet Radio communications.
 *
 *		This file contains an implementation of the "server"
 *		for the TELNET protocol.  This protocol can be used to
 *		remote-login on other systems, just like a normal TTY
 *		session.
 *
 * Usage:	telnetd [-dv]
 *
 * Version:	@(#)telnetd.c	1.00	07/26/92
 *
 * Author:	Fred N. van Kempen, <waltje@uwalt.nl.mugnet.org>
 *		Michael Temari, <temari@temari.ae.ge.com>
 */
#include "minix.h"
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#if 0
#include <ttyent.h>
#include <utmp.h>
#include <net/gen/in.h>
#include <net/gen/tcp.h>
#include <net/gen/tcp_io.h>
#include <net/gen/socket.h>
#include <net/gen/netdb.h>
#include <net/gen/inet.h>
#else
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include "telnetd.h"
#define	SOCKERR	 errno

#define	PORT		23 /* telnet */
#define	BACKLOG		5
static char *Version = "@(#) telnetd 1.00 (07/26/92)";

int opt_d = 0;				/* debugging output flag	*/
extern char **environ;
_PROTOTYPE(void usage, (void));
_PROTOTYPE(int main, (int argc, char *argv[]));
_PROTOTYPE(void wtmp, (int type, int linenr, char *line, pid_t pid,
								char *host));

void usage()
{
   fprintf(stderr, "Usage: telnetd [-dv]\n");

   exit(-1);
}

extern int opterr,optind;

int main(argc, argv)
int argc;
char *argv[];
{
char buff[128];
register int c;
int pty_fd;
pid_t pid;
int lineno;
char *tty_name;
struct ttyent *ttyp;
//nwio_tcpconf_t tcpconf;
struct hostent *hostent;
char *hostname = "localhost";


   opterr = 0;
   while ((c = getopt(argc, argv, "dv")) != EOF) switch(c) {
	case 'd':
	case 'v':
		opt_d = 1;
		break;
	default:
		usage();
   }

   /* No more arguments allowed. */
   if (optind != argc) usage();

	int l_sock, c_sock, error_value,  sin_size;
	struct sockaddr_in my_adr, their_adr;
	struct timeval timeout;
	fd_set read_handles;


	/* sock start up */
	//socketStartup();
	//atexit((void (*)(void))socketCleanup);
	printf("Line%d wait data ...\n", __LINE__);

	/* create listener socket */
	l_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(l_sock < 0)
	{
		printf("socket() failed; err=%d\n", SOCKERR);
		return 1;
	}

	memset(&my_adr, 0, sizeof(my_adr));
	my_adr.sin_family = AF_INET;
	my_adr.sin_port = htons(PORT);
	my_adr.sin_addr.s_addr = INADDR_ANY;

	printf("Line%d wait data ...\n", __LINE__);
	error_value = bind(l_sock, (struct sockaddr *)&my_adr,
		sizeof(struct sockaddr));
	if(error_value != 0)
	{
		printf("bind() failed; err=%d\n", SOCKERR);
		close(l_sock);
		return 1;
	}

	printf("Line%d wait data ...\n", __LINE__);
	error_value = listen(l_sock, BACKLOG);
	if(error_value != 0)
	{
		printf("listen() failed; err=%d\n", SOCKERR);
		close(l_sock);
		return 1;
	}

	
	printf("Line%d wait data ...\n", __LINE__);
	while (1)
	{		
		FD_ZERO(&read_handles);
		FD_SET((l_sock), &read_handles);


		timeout.tv_sec = timeout.tv_usec = 1;
		error_value = select((l_sock) + 1, &read_handles, NULL, NULL, &timeout);

		if(error_value < 0)
		{
			printf("select(l_sock) failed; err=%d\n", SOCKERR);
			exit(1);
			break;
		}

		if(error_value == 0)
			continue;

		sin_size = sizeof(struct sockaddr_in);
		c_sock = accept(l_sock,
			(struct sockaddr *)&their_adr, &sin_size);
		if(c_sock < 0)
		{
			printf("accept() failed; err=%d\n", SOCKERR);
			break;
		}
		else{

		printf("connection from %s\n",
			inet_ntoa(their_adr.sin_addr));
		break;
		}
	}

#if 0
   /* Obtain the name of the remote host. */
   if (ioctl(0, NWIOGTCPCONF, &tcpconf) < 0) {
	sprintf(buff, "Unable to obtain your IP address\r\n");
	(void) write(1, buff, strlen(buff));
	return(-1);
   }
   if ((hostent = gethostbyaddr((char *) &tcpconf.nwtc_remaddr,
			sizeof(tcpconf.nwtc_remaddr), AF_INET)) != NULL) {
	hostname = hostent->h_name;
   } else {
	hostname = inet_ntoa(tcpconf.nwtc_remaddr);
   }
   /* Try allocating a PTY. */
   if (get_pty(&pty_fd, &tty_name) < 0) {
	sprintf(buff, "I am sorry, but there is no free PTY left!\r\n");
	(void) write(1, buff, strlen(buff));
	return(-1);
   }

   /* Find the tty in the tty table. */
   lineno = 0;
   for (;;) {
	if ((ttyp = getttyent()) == NULL) {
		sprintf(buff, "Can't find %s in the tty table\r\n");
		(void) write(1, buff, strlen(buff));
	}
	if (strcmp(ttyp->ty_name, tty_name+5) == 0) break;
	lineno++;
   }
   endttyent();

   /* Initialize the connection to an 8 bit clean channel. */
   term_init();
#endif


	pid = fork();

	if (pid==0) {
		static char*args[3];

		args[0] = "/bin/bash";
		args[1] = NULL;

		int c;

		//read(0,&c,1);
		printf("start shell\n");
		dup2(c_sock, 0);
		dup2(c_sock, 1);
		dup2(c_sock, 2);
		execve(args[0], args, (char **)environ);
		printf("start shell error\n");
		exit(1);
	}else if(pid>0){
		//wait(&stat);
		printf("exit ...\n");
		exit(1);
	}else{
		perror("init shell failed\n");
		return -1;
	}

#if 0
   //pid = fork();

   /* Fork off a child process and have it execute a getty(8). */
   if ((pid) == 0) {
	   printf("entry telnetd\n");
	/* Set up a new session. */
	/*setsid();
	if ((c_sock = open(tty_name, O_RDWR)) < 0) {
		sprintf(buff, "Can't open %s\r\n", tty_name);
		(void) write(1, buff, strlen(buff));
		//return(-1);
	}


	close(pty_fd);
	dup2(c_sock, 0);
	dup2(c_sock, 1);
	dup2(c_sock, 2);*/
	printf("start /bin/sh\n");
	//close(c_sock);
	(void) execl("/bin/sh", "-", (char *)NULL);
	while (1)
	{
	}
	(void) execl("/usr/sbin/getty", "getty", (char *)NULL);
	(void) execl("/usr/bin/getty", "getty", (char *)NULL);
	(void) execl("/usr/bin/login", "login", (char *)NULL);
	(void) write(1, "EXEC failed!\r\n", 14);
   } else if (pid < 0) {
	sprintf(buff, "I am sorry, but the fork(2) call failed!\r\n");
	(void) write(1, buff, strlen(buff));
	(void) close(pty_fd);
	return(-1);
   }
   else if(pid<0){
	   write(1,"error fork ...",14);
   }

   printf("telnetd exit ...\n");
   wtmp(LOGIN_PROCESS, lineno, tty_name+5, pid, hostname);
#endif
   term_inout(pty_fd);

   (void) close(pty_fd);

#if 0
   wtmp(DEAD_PROCESS, lineno, tty_name+5, pid, hostname);
#endif
   chown(tty_name, 0, 0);
   chmod(tty_name, 0666);

   return(0);
}
