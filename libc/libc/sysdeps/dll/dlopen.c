/*****************************************************************************
LOAD AND RUN DJGPP COFF, WIN32 PE COFF, OR ELF RELOCATABLE FILE

EXPORTS
int lookup_external_symbol(char *sym_name, unsigned *adr, unsigned uscore);
*****************************************************************************/
#include <stdlib.h> /* NULL, malloc(), free() */
#include <string.h> /* strcmp() */
#include <setjmp.h> /* jmp_buf, setjmp(), longjmp() */
#include <stdio.h> /* fopen(), fseek(), ftell(), fclose(), fread() */
#include <time.h> /* time_t, time() */
#include <dlfcn.h> /* header */
#include "defs.h"



/* from DOS.H or LINUX.C */
void delay(unsigned milliseconds);


/* from DJCOFF.C */
int load_djcoff_relocatable(char *image, unsigned *entry);

/* from PECOFF.C */
int load_pecoff_relocatable(char *image, unsigned *entry);

/* from ELF.C */
int load_elf_relocatable(unsigned char *image, unsigned *entry);


static jmp_buf g_oops;
#if defined(__WIN32__)
const char *g_sys_ver = "Win32 PE COFF";
#elif defined(__DJGPP__)
const char *g_sys_ver = "DJGPP COFF";
#else
const char *g_sys_ver = "ELF";
#endif
/*****************************************************************************
*****************************************************************************/
void *dlopen (const char *__file, int __mode)
{
	unsigned char *image;
	unsigned long size;
	unsigned entry;
	int file;
	int err;

	if(setjmp(g_oops) != 0)
		return 0;

/* open file */
	file = open(__file, 0);
	if(file == NULL)
	{
		printf("Can't open file '%s\n", __file);
		return NULL;
	}

/* get size */
	lseek(file, 0, SEEK_END);
	size = filelength(file);

/* alloc mem */
	image = malloc(size);
	if(image == NULL)
	{
		printf("Out of memory\n");
		close(file);
		return NULL;
	}
/* read entire file */
	lseek(file, 0, SEEK_SET);
	read(file, image,  size);
	close(file);

/* try loading as ELF
	err = load_elf_relocatable(image, &entry);

	if(err == 0)
	return image;
	if(err < 0){
		free(image);
		return NULL;
	} */

/* try loading as COFF */
#if defined(__WIN32__)
	err = load_pecoff_relocatable(image, &entry);
#else
	err = load_djcoff_relocatable(image, &entry);
#endif

	if(err == 0)
	return image;

		free(image);
		return NULL;
}

int dlclose (void *__handle)
{
	free(__handle);
	return 0;
}

char *dlerror (void)
{
	return "unknow error";
}

