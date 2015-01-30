#ifndef __MY_DEFS_H
#define	__MY_DEFS_H

#if defined(__GNUC__)
#define	__PACKED__	__attribute__((__packed__))
#else
#define	__PACKED__	/* nothing */
//#error Need compiler voodoo to pack structures.
#endif


typedef struct
{
	unsigned short magic		__PACKED__;
	unsigned short num_sects	__PACKED__;
	unsigned long time_date	__PACKED__;
	unsigned long symtab_offset	__PACKED__;
	unsigned long num_syms	__PACKED__;
	unsigned short aout_hdr_size	__PACKED__;
	unsigned short flags		__PACKED__;
/* for executable COFF file, a.out header would go here */
} coff_file_t;

typedef struct
{
	char name[8]		__PACKED__;
	unsigned long phys_adr	__PACKED__;
	unsigned long virt_adr	__PACKED__;
	unsigned long size		__PACKED__;
	unsigned long offset		__PACKED__;
	unsigned long relocs_offset	__PACKED__;
	unsigned long line_nums_offset __PACKED__;
	unsigned short num_relocs	__PACKED__;
	unsigned short num_line_nums	__PACKED__;
	unsigned long flags		__PACKED__;
} coff_sect_t;

typedef struct
{
	unsigned long adr		__PACKED__;
	unsigned long symtab_index	__PACKED__;
	unsigned short type		__PACKED__;
} coff_reloc_t;

typedef struct
{
	union
	{
		char name[8]	__PACKED__;
		struct
		{
			unsigned long zero		__PACKED__;
			unsigned long strtab_index	__PACKED__;
		} x		__PACKED__;
	} x			__PACKED__;
	unsigned long val		__PACKED__;
	unsigned short sect_num	__PACKED__;
	unsigned short type		__PACKED__;
	unsigned char sym_class	__PACKED__;
	unsigned char num_aux		__PACKED__;
} coff_sym_t;

#endif
