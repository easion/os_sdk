include $(SDKDIR)/bin/compile.mk

LINKLIB +=   -L.  -ltcc1

all: tcc

TOBJS =  tcc.o 

tcc: $(TOBJS)
	$(LD)  $(LCFLAG) -o  $@  $(CRT0)   $(TOBJS) $(LINKLIB) 
	 $(STRIP) $@ 
	cp -fr  $@  $(SDKDIR)/livecd/iso/system/bin/


clean:
	rm -f *.o  *.bak
	rm -f hello
