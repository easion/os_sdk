/*****************************************************************************
DJGPP COFF RELOCATION

EXPORTS
int load_djcoff_relocatable(unsigned char *image, unsigned *entry);
*****************************************************************************/
#include <stdlib.h> /* calloc(), free() */
#include <string.h> /* NULL, strcmp() */
#include <stdio.h> /* printf() */
#include "defs.h"

/* IMPORTS
from COFF.C */
int get_coff_sym(unsigned char *image, unsigned i,
		unsigned *sym_val, unsigned *sect_num);
/*****************************************************************************
*****************************************************************************/
static int do_djcoff_reloc(unsigned char *image,
		coff_sect_t *sect, unsigned r)
{
	int err, r_delta, t_delta = 0;
	unsigned sym_val, sym_sect;
	coff_reloc_t *reloc;
	coff_file_t *file;
	unsigned long *where;

/* r_delta = delta (i.e. LMA - VMA) for section containing this relocation */
	r_delta = (unsigned)image + sect->offset - sect->virt_adr;
/* point to the item to be relocated */
	reloc = (coff_reloc_t *)(image + sect->relocs_offset) + r;
	where = (unsigned long *)(reloc->adr + r_delta);
/* get symbol */
	err = get_coff_sym(image, reloc->symtab_index, &sym_val, &sym_sect);
	if(err != 0)
		return err;
/* t_delta = delta for target section (section in symbol table entry) */
	file = (coff_file_t *)image;
	if(sym_sect != 0) /* internal symbol */
	{
		sect = (coff_sect_t *)(image + sizeof(coff_file_t) +
			file->aout_hdr_size) + (sym_sect - 1);
		t_delta = (unsigned)image + sect->offset - sect->virt_adr;
	}
	switch(reloc->type)
	{
/* absolute reference
COFF.H calls this "RELOC_ADDR32"; objdump calls it "dir32" */
	case 6:
		if(sym_sect == 0) /* external symbol */
			*where = sym_val;
		else
			*where += t_delta;
		break;
/* EIP-relative reference
COFF.H calls this "RELOC_REL32"; objdump calls it "DISP32" */
	case 20:
		if(sym_sect == 0) /* external symbol */
			*where += sym_val - r_delta;
/* type 20 relocation for internal symbol
does not occur with normal DJGPP code */
		else
			*where += t_delta - r_delta;
		break;
	default:
		printf("unknown relocation type %u (must be 6 or 20)\n",
			reloc->type);
		return -1;
	}
	return 0;
}
/*****************************************************************************
*****************************************************************************/
int load_djcoff_relocatable(unsigned char *image, unsigned *entry)
{
	unsigned char *bss;
	coff_sect_t *sect;
	coff_file_t *file;
	unsigned s, r;
	int err;

/* validate */
	file = (coff_file_t *)image;
	if(file->magic != 0x14C)
	{
		printf("File is not relocatable COFF; has bad magic value "
			"0x%X (should be 0x14C)\n", file->magic);
		return +1;
	}
	if(file->flags & 0x0001)
	{
		printf("Relocations have been stripped from COFF file\n");
		return +1;
	}
/* find the BSS and allocate memory for it
This must be done BEFORE doing any relocations */
	for(s = 0; s < file->num_sects; s++)
	{
		sect = (coff_sect_t *)(image + sizeof(coff_file_t) +
			file->aout_hdr_size) + s;
		if((sect->flags & 0xE0) != 0x80)
			continue;
		r = sect->size;
		bss = calloc(1, r);
		if(bss == NULL)
		{
			printf("Can't allocate %u bytes for BSS\n",
				r);
			return -1;
		}
		sect->offset = bss - image;
		break;
	}
/* for each section... */
	for(s = 0; s < file->num_sects; s++)
	{
		sect = (coff_sect_t *)(image + sizeof(coff_file_t) +
			file->aout_hdr_size) + s;
/* for each relocation... */
		for(r = 0; r < sect->num_relocs; r++)
		{
			err = do_djcoff_reloc(image, sect, r);
			if(err != 0)
				return err;
		}
		sect++;
	}
/* find start of .text and make it the entry point */
	(*entry) = 0;
	for(s = 0; s < file->num_sects; s++)
	{
		sect = (coff_sect_t *)(image + sizeof(coff_file_t) +
			file->aout_hdr_size) + s;
//		if((sect->flags & 0xE0) != 0x20)
//			continue;
		if(strcmp(sect->name, ".text"))
			continue;
		(*entry) = (unsigned)image + sect->offset;
		break;
	}
	if((*entry) == 0)
	{
		printf("Can't find section .text, so entry point is unknown\n");
		return -1;
	}
	for(s = 0; s < file->num_sects; s++)
	{
		sect = (coff_sect_t *)(image + sizeof(coff_file_t) +
			file->aout_hdr_size) + s;
		printf("%-8.8s: %lu bytes at offset=0x%lX, LMA=0x%p\n",
			sect->name, sect->size, sect->offset,
			image + sect->offset);
	}
	return 0;
}
