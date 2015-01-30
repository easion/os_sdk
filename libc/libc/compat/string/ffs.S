/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include "asm.h"
MK_C_SYM(ffs)
	bsfl	4(%esp), %eax
	jnz	.Lzero
	movl	$-1,%eax
.Lzero:
	incl 	%eax
	ret
