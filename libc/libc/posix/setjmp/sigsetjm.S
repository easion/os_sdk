/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include"asm.h"
MK_C_SYM(sigsetjmp)
	jmp	C_SYM(setjmp)

