/*
 * $XFree86: xc/programs/Xserver/hw/kdrive/vesa/vm86.c,v 1.1 2000/10/20 00:19:51 keithp Exp $
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

#include "vm86.h"


static const U8 retcode_data[2] =
{ 0xCD, 0xFF };

//#undef ErrorF

Vm86InfoPtr
Vm86Setup(Bool val)
{
   
    Vm86InfoPtr vi = NULL;
  

    vi = xalloc(sizeof(Vm86InfoRec));
    if (!vi)
	goto unmapfail;


    return vi;

unmapfail:
 
    if(vi)
	xfree(vi);
    return NULL;
}

void
Vm86Cleanup(Vm86InfoPtr vi)
{   
    xfree(vi);
}

int
Vm86DoInterrupt(Vm86InfoPtr vi, int num)
{
	int err;

    err=realint( 0x10, &vi->vms );

	if (err<0)
	{
		printf("realint error line%d\n",__LINE__);
		return -1;
	}
    
	return 0;
}





#ifdef NOT_IN_X_SERVER
static void 
ErrorF(char *f, ...)
{
#ifdef ERRORS
    va_list args;
    va_start(args, f);
    vfprintf(stderr, f, args);
   va_end(args);
#endif
}
#endif
