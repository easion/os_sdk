# Makefile for telnetd
#
# 01/25/96 Initial Release	Michael Temari, <Michael@TemWare.Com>
# 2005-02-25 version 2.00

INC_BASE = $(SDKDIR)/uclibc
ARCH_C = i386-elf-

AR = $(ARCH_C)ar rcs
CC = $(ARCH_C)gcc
CPP =$(ARCH_C)g++
LD = $(ARCH_C)ld
STRIP = $(ARCH_C)strip
CRT1 = $(INC_BASE)/lib/crt1.o

CPPFLAGS = -nostdlib -nostdinc  -I$(SDKDIR)/bin/include/c++/3.3.4  -I$(SDKDIR)/bin/include/c++/3.3.4/i386-newos -I$(SDKDIR)/bin/include/

CFLAGS = -nostdlib -nostdinc  -I$(INC_BASE)/include/
LCFLAG =  -nostdlib -nostdinc   -Ttext 0x10000  
LINKLIB = -L$(INC_BASE)/lib  -lc  -lnetbas -lgcc

//CFLAGS+=	 -D_MINIX -D_POSIX_SOURCE 
LDFLAGS=-i
BINDIR=	/usr/bin
PROG=	telnetd
MANDIR= /usr/man/man8
MANPAGE=telnetd.8

OBJS=	main.o telnet.o term.o pty.o 
#wtmp.o

all:	$(PROG)

$(PROG):	$(OBJS)
	$(LD)  $(LCFLAG) -o $@ $(CRT1)    $(OBJS)  $(LINKLIB) 
	$(STRIP)  $@ 
	cp $@  /d/jicamasdk/livecd/iso/bin/ -f
#	$(CC) $(LDFLAGS) -o $@ $(OBJS)
#	install -S 8kw $@

clean:
	rm -f $(PROG) $(OBJS)


$(BINDIR)/$(PROG):	$(PROG)
	install -cs -o bin $? $@


installman:	$(MANDIR)/$(MANPAGE)
	cp $(MANPAGE) $(MANDIR)
	echo "You may need to run makewhatis to update man page index"
