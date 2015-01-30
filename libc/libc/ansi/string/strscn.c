
#include <limits.h>
#include <string.h>


char *strscn(char *s,char *pattern)
{
    char *scan;
    while (*s != 0) {
    	scan = pattern;
    	while (*scan != 0) {
	    if (*s == *scan) return(s);
	    else scan++;
	}
	s++;
    }
    return(NULL);
}


long int strtoi(char *s,int base,char **scan_end)
{
    int sign,value,overflow = 0;
    long int result = 0,oldresult;
    /* Evaluate sign */
    if (*s == '-') {
	sign = -1;
	s++;
    } else if (*s == '+') {
	sign = 1;
	s++;
    }
    else sign = 1;
    /* Skip trailing zeros */
    while (*s == '0') s++;
    /* Convert number */
    while (isnumber(*s,base)) {
	value = tonumber(*s++);
	if (value > base || value < 0) return(0);
	oldresult = result;
	result *= base;
	result += value;
	/* Detect overflow */
	if (oldresult > result) overflow = 1;
    }
    if (scan_end != 0L) *scan_end = s;
    if (overflow) result = INT_MAX;
    result *= sign;
    return(result);
}
