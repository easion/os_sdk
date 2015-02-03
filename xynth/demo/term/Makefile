
include ../../Makefile.cfg
include ../../Makefile.parse

DIR = src/demo/term/

INCDIR  = ../../src/lib ../../../libc/include ../../../librtl ../../../posix/include
LIBDIR  = ../../src/lib ../../../libc ../../../librtl ../../../posix
#LDFLAGS = -lxynth -lrtl -lstdc -lposix -lm -ldl -lpthread ../../../libc/init/init.o
LDFLAGS = -lxynth -L$(UCLIBBINDIR)  -lnce  -lfreetype -lpng -lz $(LINKLIB) 

OBJS = xyterm.o

ifeq ($(SINGLE_APP), Y)
TARGET_A = single_term.a
CFLAGS  += -Dmain=term_main
else
TARGET = xyterm
endif

EXTRA_CLEAN = xyterm single_term.a

include ../../Makefile.rules

dist: all
ifneq ($(TARGET),)
	cp -a $(TARGET) ../../$(DISTBINDIR)
endif
