#define JICAMA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <int86.h>

static unsigned long long next = 0;

int
rand(void)
{
  next = next * 1103515245L + 12345;
  next = (next<<15) ^ (next >> 27);
  return (int)((next >> 4) & RAND_MAX);
}

void
srand(unsigned seed)
{
  next = seed;
}


 time_t clock(void);
void delay(unsigned ms)
{
    time_t end;
    end = clock() + ms;
    while (clock() < end)
        ;
}

