
# chose ELF, COFF, or PE in the next line
LSCRIPT	=$(SDKDIR)/bin/include/coff.txt

BASEDIR= $(SDKDIR)
#CC = gcc
CC = i386-elf-gcc
AR = i386-elf-ar
LD = i386-elf-ld
ASM =  i386-elf-gcc

INCDIR	=$(SDKDIR)/bin/include
CFLAGS	= -I$(INCDIR) -fno-builtin -nostdinc -MD -MT -MF

EXECLFLAGS	= -fno-builtin -nostdinc -nostdlib  -e _start -Ttext 0x1000

LD_FLAGS =  -shared -soname  --script=$(SDKDIR)/bin/templates/library.ld

COFFLD	=ld -g -T$(LSCRIPT) -nostdlib
COFFCFLAGS	= -I$(INCDIR) -fno-builtin -nostdinc 

CRT0	= $(SDKDIR)/bin/lib/crt.o
LIBS	=  $(SDKDIR)/bin/lib/libc.a
RM = rm -f
CP = cp
MV = mv

%.o%.c:
	$(CC) $(CFLAGS) -c -o $@ $<

%.o%.S:
	$(ASM) -c -o $@ $<  -I$(SDKDIR)/bin/include
