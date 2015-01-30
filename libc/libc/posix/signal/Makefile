THIS_SRCS = itimer.o kill.o sigaddse.o sigdelse.o sigempty.o sigfills.o \
	sigismem.o sigpendi.o sigprocm.o sigsuspe.o sigactio.o signal.o
include $(SDKDIR)/bin/include/djgpp.inc

all:	lib.o 

lib.o:	$(THIS_SRCS)
	$(LD) $(LD_FLAGS) -o $@ $(THIS_SRCS)

clean:
	$(RM)  *.o
	$(RM)  *.o
	$(RM)  *.bak
