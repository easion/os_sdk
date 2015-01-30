INC_BASE = $(SDKDIR)/bin
ARCH_C = i386-elf-
CROSS=i386-elf-
#AR = $(ARCH_C)ar rcs
AR = $(ARCH_C)ar 
CC = $(ARCH_C)gcc
CPP =$(ARCH_C)g++
CXX =$(ARCH_C)g++

LD = $(ARCH_C)ld
STRIP = $(ARCH_C)strip -s
OBJDUMP = $(ARCH_C)objdump
UCLIBDIR=$(SDKDIR)/uclibc/
UCLIBBINDIR=$(UCLIBDIR)/lib/
RANLIB = $(ARCH_C)ranlib
AR = $(ARCH_C)ar

INSTALL_DIR=$(SDKDIR)/livecd/iso/
SO_DIR=$(INSTALL_DIR)/system/lib/

PWD 	:= $(shell pwd)

SDLDIR=-I$(UCLIBDIR)/include/SDL -I$(UCLIBDIR)/include/freetype2  
CFLAGS += -g -nostdlib -nostdinc  -I$(UCLIBDIR)/include 
CPPFLAGS += $(CFLAGS) -g  -Wall -O3

CXXFLAGS := $(CPPFLAGS)  -Wall -Wshadow -Wnon-virtual-dtor \
	    -Wno-parentheses -Wno-pmf-conversions -Wno-pointer-arith \
	    -Wno-unused-function -Wundef -fno-rtti -fno-exceptions \


LINKLIB = -L$(UCLIBBINDIR) -lm -lnetbas   -lc -lgcc
DYLINKLIB = -L$(UCLIBBINDIR) -lm -lnetbas $(SO_DIR)/libc.so -lgcc
LINK_CPP_LIB =  -L$(UCLIBBINDIR)    -lstdc++   -lm  -lnetbas -lc -lgcc 
LCFLAG =  -nostdlib -nostdinc --script=$(SDKDIR)/bin/app.ld
LCFLAG_DY =   --script=$(SDKDIR)/bin/app.ld

CRT0=$(UCLIBDIR)/lib/crt0.o
CRT1=$(UCLIBDIR)/lib/crt1.o
CRTDY=$(UCLIBDIR)/lib/crt_dy.o
CRTI=$(UCLIBDIR)/lib/crti.o
CRTN=$(UCLIBDIR)/lib/crtn.o


OBJECTS = $(SOURCES:.cpp=.o)
.SUFFIXES: .cpp .o

%.o%.c:
	$(CC) $(CFLAGS) -c -o $@ $<

.cpp.o:
	$(CPP) $(CPPFLAGS) -c -o $@ $<





