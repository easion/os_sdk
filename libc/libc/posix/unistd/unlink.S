/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */

//#define NEEDS_UNDERSCORES

#ifndef NEEDS_UNDERSCORES

#define C_SYM(x)	x
#else

#define C_SYM(x)	_##x

#endif

#define MK_C_SYM(x)	C_SYM(x) : ; \
			.globl C_SYM(x)

MK_C_SYM(unlink)
	jmp	C_SYM(remove)
