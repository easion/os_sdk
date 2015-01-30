
# main libc
LIBS_DIR=$(SDKDIR)/bin/
LIBS_BUILD_DIR=$(SDKDIR)/bin/libc/
MY_TARGET := $(LIBS_BUILD_DIR)/libc.so
MY_STATIC_TARGET := $(LIBS_BUILD_DIR)/libc.a
LIBS_LDSCRIPT=$(SDKDIR)/bin/templates/library.ld

LIBC_EXTRA_CFLAGS := -D__STDC_VERSION__=199901

MY_TARGETDIR := $(SDKDIR)/bin/libc/
MY_SRCDIR := $(LIBS_DIR)/libc
MY_OBJS := \
	libc_init.o

MY_INCLUDES := $(STDINCLUDE)
MY_CFLAGS := $(USER_CFLAGS) $(LIBC_EXTRA_CFLAGS)
MY_CPPFLAGS := $(USER_CFLAGS) $(LIBC_EXTRA_CFLAGS)
MY_LINKSCRIPT := $(LIBS_LDSCRIPT)

# include sub makefiles

include $(addsuffix /Makefile, $(addprefix $(MY_SRCDIR)/, \
	dos \
	net \
	sysdeps \
	libcon2 \
	ansi \
	posix \
	compat \
))

include  $(SDKDIR)/bin//templates/lib.mk

clean:
	rm -fr $(MY_OBJS)

install:
	$(CP)  libc.so  ./../lib
	$(CP)  libc.so.a ./../lib/libstdc.a
	rm -f *.o *.d