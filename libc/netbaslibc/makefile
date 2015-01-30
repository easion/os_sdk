
# main libc
LIBS_DIR=$(SDKDIR)/bin/
LIBS_BUILD_DIR=$(SDKDIR)/bin/netbaslibc/
MY_TARGET := $(LIBS_BUILD_DIR)/netbas.so
MY_STATIC_TARGET := $(LIBS_BUILD_DIR)/libnetbas.a
LIBS_LDSCRIPT=$(SDKDIR)/bin/templates/library.ld

MY_CFLAGS_IN = -I$(SDKDIR)/uclibc/include -I.
CPPFLAGS += -I$(SDKDIR)/uclibc/include ./

LIBC_EXTRA_CFLAGS := -D__STDC_VERSION__=199901

MY_TARGETDIR := $(SDKDIR)/bin/netbaslibc/
MY_SRCDIR := $(LIBS_DIR)/netbaslibc


MY_INCLUDES := $(STDINCLUDE) -I.
MY_CFLAGS := $(USER_CFLAGS) $(LIBC_EXTRA_CFLAGS)
MY_CPPFLAGS := $(USER_CFLAGS) $(LIBC_EXTRA_CFLAGS)
MY_LINKSCRIPT := $(LIBS_LDSCRIPT)

# include sub makefiles
#	pthread \
#	inet \

include $(addsuffix /Makefile, $(addprefix $(MY_SRCDIR)/, \
	sysdeps \
))
#	malloc \

include  $(SDKDIR)/bin//templates/lib.mk

clean:
	rm -fr $(MY_OBJS)
	rm -f *.o *.d *.a *.so
	
UCLIBBINDIR=$(SDKDIR)/uclibc/lib/

install:
	$(CP)  netbas.so  $(UCLIBBINDIR)//lib
	$(CP)  netbas.so.a $(UCLIBBINDIR)/libnetbas.a
