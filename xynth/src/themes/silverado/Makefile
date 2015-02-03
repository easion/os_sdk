
include ../../../Makefile.cfg
include ../../../Makefile.parse

DIR = src/themes/silverado/

OBJS          = silverado.o
INCDIR        = ../../lib ../../server ../../../../librtl ../../../../libc/include ../../../../posix/include
TARGET_SO     = silverado.so
LDFLAGS	  += 
include ../../../Makefile.rules

dist: all
	cp -a $(TARGET_SO) ../../../$(DISTTHEMEDIR)
