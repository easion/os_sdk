

INC_BASE = $(SDKDIR)/bin
ARCH_C = i386-elf-

AR = $(ARCH_C)ar rcs
CC = $(ARCH_C)gcc
CPP =$(ARCH_C)g++
LD = $(ARCH_C)ld
STRIP = $(ARCH_C)strip -s
OBJDUMP = $(ARCH_C)objdump

CFLAGS = -nostdlib -nostdinc  -I$(SDKDIR)/uClibc-0.9.26/include 
LINKLIB = -L$(INC_BASE)/uclibc -lpthread   -lc 
LCFLAG =  -nostdlib -nostdinc 
CRT0=$(SDKDIR)/bin/uclibc/crt0.o

OBJS = test.o
ELFOBJS = elftest.o 

all:  elftest
#test.so	
#clean

elftest:$(ELFOBJS) 
	$(CC) -c crt0.S
	$(LD)  $(LCFLAG) -o $@ $(CRT0)    $(ELFOBJS)  $(LINKLIB) 
	 $(OBJDUMP) -axh $@  > elftest.lst
	 $(STRIP)  $@ 

test.so: 	$(OBJS) 
	$(LD) -shared -o $@  $(OBJS) $(LINKLIB)

clean:
	$(RM)  *.o
	$(RM)  *.a
	$(RM)  *.bak


