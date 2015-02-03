#ifndef STDIO_H
#define STDIO_H

static inline unsigned int do_system_call(int function_number,unsigned p1,unsigned p2,
                  unsigned p3,unsigned p4,unsigned p5)
{
     int return_value;
    __asm__ volatile ("int $0x80" \
        : "=a" (return_value) \
        : "0" ((long)(function_number)),"b" ((long)(p1)),"c" ((long)(p2)), \
          "d" ((long)(p3)),"S" ((long)(p4)),"D" ((long)(p5)) ); \
    return return_value;
};
#endif