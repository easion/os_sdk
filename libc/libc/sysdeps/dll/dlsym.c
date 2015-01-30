/*****************************************************************************
SYMBOL TABLE LOOKUP FOR DJGPP COFF AND WIN32 PE COFF

EXPORTS:
int get_coff_sym(unsigned char *image, unsigned i,
		unsigned *sym_val, unsigned *sect_num);
*****************************************************************************/
#include <stdio.h> /* printf() */
#include "defs.h"
enum
{
	NULL_CLASS = 0, AUTOMATIC_CLASS, EXTERNAL_CLASS, STATIC_CLASS, 
	REGISTER_CLASS, MEMBER_OF_STRUCT_CLASS, STRUCT_TAG_CLASS, 
	MEMBER_OF_UNION_CLASS, UNION_TAG_CLASS, TYPE_DEFINITION_CLASS, 
	FUNCTION_CLASS, FILE_CLASS
} ;
	
  void *dlsym (void * image,
		    const char * __name)
{
	int  pos, i;
	char *sym_name, *strtab;
	coff_file_t *file;
	coff_sym_t *sym;

	
	file = (coff_file_t *)image;

	if (file->magic!=0x14C)
	{
		return 0;
	}

	for (pos=0; pos<file->num_syms; pos++)
	{
	sym = (coff_sym_t *)(image + file->symtab_offset) + pos;
	sym_name = sym->x.name;

	if (sym->sym_class!=EXTERNAL_CLASS)continue; /*skip all other class  type*/
	
	if(sym->x.x.zero == 0)
	{
		strtab = (char *)image + file->symtab_offset +
			file->num_syms * sizeof(coff_sym_t);
		sym_name = strtab + sym->x.x.strtab_index;
	}

	if((strcmp(__name, sym_name)==0))
		{	
		//printf("%s  Found, Class %d, Address %x!\n", sym_name, sym->sym_class, sym->val);
		return ( void *)sym->val;
	}
	}


	return NULL;
}


