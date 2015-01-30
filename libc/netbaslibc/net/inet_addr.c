/*
 * Copyright (c) 1983, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>

/*
 * Ascii internet address interpretation routine.
 * The value returned is in network order.
 */
unsigned long
inet_addr(cp)
	register const char *cp;
{
	struct in_addr val;

	if (inet_aton(cp, &val))
		return (val.s_addr);
	return (INADDR_NONE);
}

//
// inet_addr
//

unsigned long inet_addr2(const char *cp)
{
  static const unsigned long max[4] = {0xFFFFFFFF, 0xFFFFFF, 0xFFFF, 0xFF};
  unsigned long val;
  char c;
  union iaddr 
  {
    unsigned char bytes[4];
    unsigned long word;
  } res;
  unsigned char *pp = res.bytes;
  int digit;
  int base;

  res.word = 0;

  c = *cp;
  for (;;) 
  {
    // Collect number up to ``.''.
    // Values are specified as for C: 0x=hex, 0=octal, isdigit=decimal.

    if (c < '0' || c > '9') 
    {
      errno = EINVAL;
      return INADDR_NONE;
    }

    val = 0; base = 10; digit = 0;
    if (c == '0') 
    {
      c = *++cp;
      if (c == 'x' || c == 'X')
        base = 16, c = *++cp;
      else 
      {
	base = 8;
	digit = 1;
      }
    }

    for (;;) 
    {
      if (c >= '0' && c <= '9') 
      {
	if (base == 8 && (c == '8' || c == '9')) 
	{
	  errno = EINVAL;
	  return INADDR_NONE;
	}
	val = (val * base) + (c - '0');
	c = *++cp;
	digit = 1;
      } 
      else if (base == 16 && c >= 'a' && c <= 'f') 
      {
	val = (val << 4) | (c + 10 - 'a');
	c = *++cp;
	digit = 1;
      } 
      else if (base == 16 && c >= 'A' && c <= 'F') 
      {
	val = (val << 4) | (c + 10 - 'A');
	c = *++cp;
	digit = 1;
      } 
      else
        break;
    }

    if (c == '.') 
    {
      // Internet format:
      //   a.b.c.d
      //   a.b.c	(with c treated as 16 bits)
      //   a.b		(with b treated as 24 bits)

      if (pp > res.bytes + 2 || val > 0xFF) 
      {
	errno = EINVAL;
	return INADDR_NONE;
      }
      *pp++ = (unsigned char) val;
      c = *++cp;
    } 
    else
      break;
  }

  // Check for trailing characters.
  if (c > ' ') 
  {
    errno = EINVAL;
    return INADDR_NONE;
  }

  // Did we get a valid digit?
  if (!digit) 
  {
    errno = EINVAL;
    return INADDR_NONE;
  }

  // Check whether the last part is in its limits depending on 
  // the number of parts in total.
  if (val > max[pp - res.bytes]) 
  {
    errno = EINVAL;
    return INADDR_NONE;
  }

  return res.word | htonl(val);
}
