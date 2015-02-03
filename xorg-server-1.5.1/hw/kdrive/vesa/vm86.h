/*
 * $XFree86: xc/programs/Xserver/hw/kdrive/vesa/vm86.h,v 1.1 2000/10/20 00:19:51 keithp Exp $
 *
 * Copyright ?2000 Keith Packard, member of The XFree86 Project, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Keith Packard not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Keith Packard makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
/* 
Copyright (c) 2000 by Juliusz Chroboczek
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions: 
 
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software. 

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _VM86_H_
#define _VM86_H_

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/vm86.h>
#include <sys/io.h>

#ifdef NOT_IN_X_SERVER
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
static void ErrorF(char*, ...);
#define xalloc(a) malloc(a)
#define xcalloc(a,b) calloc(a,b)
#define xfree(a) free(a)
#else
#include "X.h"
#include "Xproto.h"
#include "Xos.h"
#include "os.h"
#endif

#define JICAMA
#include <stdio.h>
#include <string.h>
#include <netbas/farptr.h>
#include <netbas/int86.h>

typedef unsigned char	U8;
typedef unsigned short	U16;
typedef unsigned int	U32;




typedef struct _Vm86InfoRec {
    //void		*magicMem, *loMem, *hiMem;
    //U32			brk;
    //struct vm86_struct	vms;
    //U32			ret_code, stack_base;
	vm86regs_t vms;
} Vm86InfoRec, *Vm86InfoPtr;

#define VM86_BASE_ADDR (void*)0x9000

//#define MAKE_POINTER(seg, off) (((((unsigned int)(seg))<<4) + (unsigned int)(off)))
#define MAKE_POINTER(seg, off) ((seg)+(off))
#define MAKE_POINTER_1(lw) MAKE_POINTER(((lw)&0xFFFF0000)>>12, (lw)&0xFFFF)


#define Vm86MemoryW(x,n) _farpeekw(USER_GLOBAL_DATA, (n))
#define Vm86Memory(x,n) _farpeekb(USER_GLOBAL_DATA, (n))

Vm86InfoPtr
Vm86Setup(Bool val);
    
void
Vm86Cleanup(Vm86InfoPtr vi);

int
Vm86DoInterrupt(Vm86InfoPtr vi, int num);


#endif /* _VM86_H_ */
