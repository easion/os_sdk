INC_BASE = $(SDKDIR)/bin
ARCH_C = i386-elf-
CROSS=i386-elf-
#AR = $(ARCH_C)ar rcs
AR = $(ARCH_C)ar 
CC = $(ARCH_C)gcc
CPP =$(ARCH_C)g++
LD = $(ARCH_C)ld
STRIP = $(ARCH_C)strip -s
OBJDUMP = $(ARCH_C)objdump
UCLIBDIR=$(SDKDIR)/uclibc/
UCLIBBINDIR=$(UCLIBDIR)/lib/

INSTALL_DIR=$(SDKDIR)/livecd/iso/
PWD 	:= $(shell pwd)


CFLAGS = -nostdlib -nostdinc  
CPPFLAGS += -nostdlib -nostdinc  -I$(UCLIBDIR)/include/c++/3.3.4\
-I$(UCLIBDIR)/include/c++/3.3.4/i386-newos  \
-I./include -I$(UCLIBDIR)/include/freetype2 

CXXFLAGS := $(CPPFLAGS)  -Wall -Wshadow -Wnon-virtual-dtor \
	    -Wno-parentheses -Wno-pmf-conversions -Wno-pointer-arith \
	    -Wno-unused-function -Wundef -fno-rtti -fno-exceptions \


LINKLIB = -L$(UCLIBBINDIR)  -lnetbas  -lc 
LINK_CPP_LIB =  -L$(UCLIBBINDIR)    -lstdc++   -lnetbas  -lc -lgcc 
LCFLAG =  -nostdlib -nostdinc 

CRT0=$(UCLIBDIR)/lib/crt0.o
CRT1=$(UCLIBDIR)/lib/crt1.o
CRTI=$(UCLIBDIR)/lib/crti.o
CRTN=$(UCLIBDIR)/lib/crtn.o


OBJECTS = $(SOURCES:.cpp=.o)
.SUFFIXES: .cpp .o

%.o%.c:
	$(CC) $(CFLAGS) -c -o $@ $<

.cpp.o:
	$(CPP) $(CPPFLAGS) -c -o $@ $<



%.o: %.cc
	$(CC) $(CXXFLAGS)  -o $@ $<


