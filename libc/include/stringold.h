
#ifndef STRING_H
#define STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
	char *	strdup(const char *_s);

char *strcpy(char *to, const char *from);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
int strcmp(const char *s1, const char *s2);
size_t strcspn(const char *s1, const char *s2);
int strcoll(const char *s1, const char *s2);
size_t strspn(const char *s1, const char *s2);
char *strstr(const char *s, const char *find);
char *strncat(char *dst, const char *src, size_t n);
char *strncpy(char *dst, const char *src, size_t n);
int strncmp(const char *s1, const char *s2, size_t n);
void*    memset(void* dest, int c, size_t count);
int      strlen(const char*);
void *	memcpy(void *_dest, const void *_src, size_t _n);
int	strcasecmp(const char *_s1, const char *_s2);
void	qsort(void *_base, size_t _nelem, size_t _size,
	      int (*_cmp)(const void *_e1, const void *_e2));
double cos( double angle );
double fabs( double __x );
double sin( double angle );
double sqrt( double x );
double tan( double __x );

void *	calloc(size_t _nelem, size_t _size);

#ifdef __cplusplus
}
#endif

#endif

