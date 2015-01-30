#if __STDC__ == 1
#define _ANSI		31459	/* compiler claims full ANSI conformance */
#endif

#ifdef __GNUC__
#define _ANSI		31459	/* gcc conforms enough even in non-ANSI mode */
#endif

#ifdef _ANSI
/* Keep everything for ANSI prototypes. */
#define	_PROTOTYPE(function, params)	function params
#define	_ARGS(params)			params

#define	_VOIDSTAR	void *
#define	_VOID		void
#define	_CONST		const
#define	_VOLATILE	volatile
#define _SIZET		size_t

#else

/* Throw away the parameters for K&R prototypes. */
#define	_PROTOTYPE(function, params)	function()
#define	_ARGS(params)			()
#error no ansi env here

#define	_VOIDSTAR	void *
#define	_VOID		void
#define	_CONST
#define	_VOLATILE
#define _SIZET		int

#endif /* _ANSI */

#ifndef _NSIG
#define _NSIG             32	/* number of signals used */
#endif

#define MINIX_SYMBOL(sym_name) (minix_#sym_name)
//MINIX_SYMBOL(itoa)

#define CHARBITS 0377
#define NSUBEXP  10

typedef struct regexp {
	const char *startp[NSUBEXP];
	const char *endp[NSUBEXP];
	char regstart;		/* Internal use only. */
	char reganch;		/* Internal use only. */
	char *regmust;		/* Internal use only. */
	int regmlen;		/* Internal use only. */
	char program[1];	/* Unwarranted chumminess with compiler. */
} regexp;


/* Magic numbers suggested or required by Posix specification */
#define SUCCESS	0		/* exit code in case of success */
#define FAILURE 1		/*                   or failure */

/* How to exit the system. */
#define RBT_HALT	   0
#define RBT_REBOOT	   1
#define RBT_PANIC	   2	/* for servers */
#define RBT_MONITOR	   3	/* let the monitor do this */
#define RBT_RESET	   4	/* hard reset the system */

#define MSDOS_ISVOLUME(attribute)		(((attribute) &0x20) && ((attribute) & 0x08))
#define MSDOS_ISDIR(attribute)		(((attribute) &0x10) && !((attribute) & 0x08))
#define MSDOS_ISREG(attribute)		(!((attribute) & 0x08) && !((attribute) &0x10))

union dos_time{
 struct {
  unsigned sec:5;
  unsigned min:6;
  unsigned hour:5;
	}__attribute__((packed))  t1;

	unsigned short t2;
};

union dos_date{
 struct  {
  unsigned day_of_month:5;
  unsigned month:4;
  unsigned year:7; /* since 1980 */
	}__attribute__((packed))  d1;

	unsigned short d2;
};

void prs(s);
