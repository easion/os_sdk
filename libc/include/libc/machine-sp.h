/* Machine-specific function to return the stack pointer.  i386 version.
Copyright (C) 1994 Free Software Foundation, Inc.
This file is part of the GNU C Library.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA.  */

#ifndef _MACHINE_SP_H
#define _MACHINE_SP_H

/* Return the current stack pointer.  */

#ifndef _EXTERN_INLINE
#define _EXTERN_INLINE extern __inline
#endif

_EXTERN_INLINE void *
__thread_stack_pointer (void)
{
  void *__sp__;
  __asm__ ("movl %%esp, %0" : "=r" (__sp__));
  return __sp__;
}

#endif	/* machine-sp.h */

