
CC = tcc

INCDIR	=/bin/include
CFLAGS	=-Wall -W -O2 -I$(INCDIR) -nostdinc

%.o%.c:
	$(CC) $(CFLAGS) -c -o $@ $<

RM = del

OBJS = unicode/case.o unicode/convers.o unicode/utf8.o unicode/utf16.o ctime.o\
 ./stdio/open.o ./stdio/scanf.o ./stdio/doprnt.o \
  ./stdio/stdio.o ./stdio/snprintf.o ./stdio/readdir.o\
 ./stdio/fclose.o ./stdio/fgetc.o ./stdio/fgets.o ./stdio/perror.o\
 ./stdio/fputc.o ./stdio/fputs.o ./stdio/fread.o ./stdio/fscanf.o\
 ./stdio/ftell.o ./stdio/fseek.o ./stdio/fwrite.o ./stdio/getchar.o\
 ./stdio/rewind.o  ./stdio/fprintf.o ./stdio/doscan.o\
 ./stdio/puts.o ./stdio/putchar.o ./stdio/gets.o ./stdio/fflush.o\
 ./string/strscn.o\
 ./string/strtoll.o\
stdlib/abort.o stdlib/atexit.o stdlib/atol.o stdlib/environ.o stdlib/malloc.o  stdlib/string.o \
stdlib/errno.o stdlib/exit.o stdlib/getopt.o stdlib/getenv.o stdlib/stdlib.o  stdlib/rand.o\
stdlib/strpbrk.o  stdlib/strtol.o stdlib/strtoul.o stdlib/qsort.o stdlib/conio.o\
 libc.o   signal.o  setjmp.o   farptr.o    exec.o   float.o libtcc1.o\
 syserr1.o  syserr2.o  syserr3.o\

OBJS += ./server/api.o
OBJS += ./server/dev.o
OBJS += ./server/tty.o
OBJS += ./server/gfx.o
OBJS += ./server/gfxserver.o
OBJS += ./server/fs.o

OBJS += ./bios/biosdisk.o
OBJS += ./bios/bioscom.o
OBJS += ./bios/biosequi.o
OBJS += ./bios/bioskey.o
OBJS += ./bios/biosmem.o
OBJS += ./bios/biosprin.o
OBJS += ./bios/biostime.o
OBJS += ./bios/b_time.o
OBJS += ./bios/pci.o
OBJS += ./bios/dos.o
OBJS += ./bios/disk.o
OBJS += ./bios/bios_apm.o
OBJS += ./bios/vesa.o

all:   libtcc1.a	clean


libtcc1.a: 	$(OBJS) 
	ar rsv $@  $(OBJS)
	copy $@ .\..\lib
	$(RM) $@

clean:  
	$(RM) stdio\*.o
	$(RM) stdlib\*.o
	$(RM) stdio\*.bak
	$(RM) stdlib\*.bak
	$(RM) bios\*.o
	$(RM) audio\*.o
	$(RM) server\*.o
	$(RM) server\*.bak
	$(RM) unicode\*.bak
	$(RM) unicode\*.o
	del *.bak
	


