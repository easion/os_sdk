
include ../../../Makefile.cfg
include ../../../Makefile.parse
CC=i386-elf-gcc
DIR = src/widget/widgetc/

LDFLAGS = ../../lib/expat/libexpat.o -L../../../../librtl -L../../../../libc -L../../../../posix -lrtl -lstdc -lposix -lm -lpthread ../../../../libc/init/init.o
INCDIR = ./ ../ ../../lib ../../../../librtl ../../../../libc/include ../../../../posix/include

OBJS = widgetc.o list.o code.o header.o xml.o

TARGET_HOST = widgetc

#CC := PATH=/usr/bin:${PATH} gcc

include ../../../Makefile.rules

dist: all
ifneq ($(TARGET),)
	cp -a $(TARGET) ../../../$(DISTBINDIR)
endif
