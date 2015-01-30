#include <time.h>
#include <assert.h>

#define BCD_TO_BIN(val) ((val)=((val)&15) + ((val)>>4)*10)

