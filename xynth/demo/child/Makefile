
include ../../Makefile.cfg
include ../../Makefile.parse

DIR = src/demo/child/

INCDIR  = ../../src/lib
LIBDIR  = ../../src/lib
LDFLAGS = -lxynth -L$(UCLIBBINDIR)  -lnce  -lfreetype -lpng -lz $(LINKLIB) 

OBJS = child.o

ifeq ($(SINGLE_APP), Y)
TARGET_A = single_child.a
CFLAGS  += -Dmain=child_main
else
TARGET = child
endif

EXTRA_CLEAN = child single_child.a

include ../../Makefile.rules

dist: all
ifneq ($(TARGET),)
	cp -a $(TARGET) ../../$(DISTBINDIR)
endif
