#ifndef _LIBC_SYMBOLS_H
#define _LIBC_SYMBOLS_H	1

#define _LIBC	1
#define _GNU_SOURCE	1
#define _REENTRANT	1
#define __SYMBOL_PREFIX "_"

#define strong_alias(original, alias)	\
  asm (__string_1 (ASM_GLOBAL_DIRECTIVE) " " __SYMBOL_PREFIX #alias "\n" \
       ".set " __SYMBOL_PREFIX #alias "," __SYMBOL_PREFIX #original);

#define __string_1(x) __string_0(x)
#define __string_0(x) #x

#define weak_extern_asm(symbol)	asm (".weak " __SYMBOL_PREFIX #symbol);
#define weak_alias_asm(original, alias) \
  asm (".weak " __SYMBOL_PREFIX #alias "\n" \
       __SYMBOL_PREFIX #alias " = " __SYMBOL_PREFIX #original);

#define weak_alias_asm2(original, alias) \
  asm (".weak " __SYMBOL_PREFIX alias "\n" \
       __SYMBOL_PREFIX alias " = " __SYMBOL_PREFIX original);

#define weak_alias(o, a) weak_alias_asm (o, a)
#define weak_alias2(o, a) weak_alias_asm2 (o, a)
#define weak_extern(symbol) weak_extern_asm (symbol)

#define weak_function __attribute__ ((weak))
#define weak_const_function __attribute__ ((weak, __const__))

#endif /* libc-symbols.h */
