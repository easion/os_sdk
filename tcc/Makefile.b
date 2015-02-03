
# chose ELF, COFF, or PE in the next line

CC = i386-elf-gcc
INC_BASE = /sdk/bin

include /sdk/bin/include/djgpp.inc

CFLAGS = -I$(INC_BASE)/include -I$(INC_BASE)/include/SDL  -mpreferred-stack-boundary=2  -nostdinc -ffreestanding   -O2 -g -Wall  -march=i386 

CRT0	= $(INC_BASE)/lib/crt0.o
LIBCS	=  $(INC_BASE)/lib/libc.a


.c.o:
	$(CC) -c $(CFLAGS) -o $@ $*.c

all: tcc

clean:
	$(RM) tcc
	for %f in ( *.bak *.o *.exe) do del %f

tcc: tcc.o 
	$(LD)  -Ttext 0x1000  -nosdtinc -o $@  $(CRT0)  $@.o    $(LIBCS)

