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

#define _NSIG             32	/* number of signals used */
#define MINIX_SYMBOL(sym_name) (minix_#sym_name)
//MINIX_SYMBOL(itoa)



