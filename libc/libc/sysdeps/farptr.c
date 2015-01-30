#if 1
 void
_farpokeb(unsigned short selector,
	 unsigned long offset,
	 unsigned char value)
{
#ifndef __TINYC__ 
  __asm__ __volatile__ ("movw %w0,%%fs\n"
      "	.byte 0x64 \n"
      "	movb %b1,(%k2)"
      :
      : "rm" (selector), "qi" (value), "r" (offset));
#endif
}

 void
_farpokew(unsigned short selector,
	 unsigned long offset,
	 unsigned short value)
{
#ifndef __TINYC__ 
  __asm__ __volatile__ ("movw %w0,%%fs \n"
      "	.byte 0x64 \n"
      "	movw %w1,(%k2)"
      :
      : "rm" (selector), "ri" (value), "r" (offset));
#endif
}

 void
_farpokel(unsigned short selector,
	 unsigned long offset,
	 unsigned long value)
{
 #ifndef __TINYC__ 
 __asm__ __volatile__ ("movw %w0,%%fs \n"
      "	.byte 0x64 \n"
      "	movl %k1,(%k2)"
      :
      : "rm" (selector), "ri" (value), "r" (offset));
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////
 unsigned char
_farpeekb(unsigned short selector,
	 unsigned long offset)
{
  unsigned char result;
#ifndef __TINYC__ 
  __asm__ __volatile__ ("movw %w1,%%fs \n"
      "	.byte 0x64 \n"
      "	movb (%k2),%b0"
      : "=q" (result)
      : "rm" (selector), "r" (offset));
#endif
  return result;
}

void _farnspokeb(unsigned long offset,
	 unsigned char value)
{
#ifndef __TINYC__ 
  __asm__ __volatile__ (".byte 0x64\n"
      "	movb %b0,(%k1)"
      :
      : "qi" (value), "r" (offset));
#endif
}

 unsigned short
_farpeekw(unsigned short selector,
	 unsigned long offset)
{
  unsigned short result;
#ifndef __TINYC__ 
  __asm__ __volatile__ ("movw %w1, %%fs \n"
      "	.byte 0x64 \n"
      "	movw (%k2),%w0 \n"
      : "=r" (result)
      : "rm" (selector), "r" (offset));
#endif
  return result;
}

 unsigned long
_farpeekl(unsigned short selector,
	 unsigned long offset)
{
  unsigned long result;
#ifndef __TINYC__ 
  __asm__ __volatile__ ("movw %w1,%%fs\n"
      "	.byte 0x64\n"
      "	movl (%k2),%k0"
      : "=r" (result)
      : "rm" (selector), "r" (offset));
#endif
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////
 void
_farsetsel(unsigned short selector)
{
#ifndef __TINYC__ 
  __asm__ __volatile__ ("movw %w0,%%fs"
      :
      : "rm" (selector));
#endif
}

 unsigned short
_fargetsel(void)
{
  unsigned short selector;
#ifndef __TINYC__ 
  __asm__ __volatile__ ("movw %%fs,%w0 \n"
      : "=r" (selector)
      : );
#endif
  return selector;
}

//////////////////////write mode////////////////////////////////////////////////////

 void
_farnspokew(unsigned long offset,
	 unsigned short value)
{
#ifndef __TINYC__ 
  __asm__ __volatile__ (".byte 0x64\n"
      "	movw %w0,(%k1)"
      :
      : "ri" (value), "r" (offset));
#endif
}

 void
_farnspokel(unsigned long offset,
	 unsigned long value)
{
#ifndef __TINYC__ 
  __asm__ __volatile__ (".byte 0x64\n"
      "	movl %k0,(%k1)"
      :
      : "ri" (value), "r" (offset));
#endif
}
///////////////////////read mode////////////////////////////////////////////////////////////////////////////
 unsigned char
_farnspeekb(unsigned long offset)
{
  unsigned char result;
#ifndef __TINYC__ 
  __asm__ __volatile__ (".byte 0x64\n"
      "	movb (%k1),%b0"
      : "=q" (result)
      : "r" (offset));
#endif
  return result;
}

 unsigned short
_farnspeekw(unsigned long offset)
{
  unsigned short result;
 #ifndef __TINYC__ 
 __asm__ __volatile__ (".byte 0x64\n"
      "	movw (%k1),%w0"
      : "=r" (result)
      : "r" (offset));
#endif
  return result;
}

 unsigned long
_farnspeekl(unsigned long offset)
{
  unsigned long result;
#ifndef __TINYC__ 
  __asm__ __volatile__ (".byte 0x64\n"
      "	movl (%k1),%k0"
      : "=r" (result)
      : "r" (offset));
 #endif
 return result;
}
#endif



void my_logpnt(char *tbuf)
{
	write(1, tbuf, strlen(tbuf)+1);
}


