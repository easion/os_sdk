

include $(SDKDIR)/bin/include/djgpp.inc


OBJS = thread.o msgport.o

all: libthread.o

libthread.o:	$(OBJS)
	$(LD) $(LD_FLAGS) -o $@ $(OBJS)

clean:
	$(RM)  *.o
	$(RM)  *.o
	$(RM)  *.bak
