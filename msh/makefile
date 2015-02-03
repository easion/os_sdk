
include $(SDKDIR)/bin/compile.mk

CFLAGS +=  -I./ -D_JICAMA -D_POSIX_SOURCE -Wall -O3 


all:   sh

TOBJS = sh1.o sh2.o sh3.o sh4.o sh5.o sh6.o sh3_j.o\
touch.o uname.o test.o 


sh: $(TOBJS)
	$(LD)  $(LCFLAG) -o $@ $(CRT0)    $(TOBJS)  $(LINKLIB) 
	 $(STRIP)  $@ 
	cp $@ $(SDKDIR)/livecd/iso/system/bin/ -fr


clean:
	rm -f *.o  *.bak 
	rm -f sh 
