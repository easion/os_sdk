THIS_SRCS = times.o
include $(SDKDIR)/bin/include/djgpp.inc

all:	lib.o 

lib.o:	$(THIS_SRCS)
	$(LD) $(LD_FLAGS) -o $@ $(THIS_SRCS)

clean:
	$(RM)  *.o
	$(RM)  *.o
	$(RM)  *.bak
