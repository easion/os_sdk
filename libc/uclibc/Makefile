

TOPDIR=../
include $(TOPDIR)Rules.mak

ifeq ($(strip $(UCLIBC_CTOR_DTOR)),y)
CRTOBJS=../../lib/crti.o ../../lib/crt0.o ../../lib/crtn.o
else
CRTOBJS=../../lib/crt0.o
endif

DIRS = misc pwd_grp stdio string termios inet signal stdlib sysdeps unistd execinfo libpthread inet netbas

# Check if the target architecture has a version script for
# libc, and if so, include it when linking.
VERSION_SCRIPT:=${shell if [ -f sysdeps/linux/$(TARGET_ARCH)/libc.map ] ; then \
        echo "--version-script sysdeps/linux/$(TARGET_ARCH)/libc.map"; fi}

#all: halfclean subdirs $(LIBNAME) $(DO_SHARED)
all:  $(LIBNAME) shared

ar-target:
	$(CROSS)ranlib ../libc/$(LIBNAME)
	cp -fr  ../libc/$(LIBNAME)  $(SDKDIR)/uclibc/lib/ -fr
#	$(INSTALL) -d $(TOPDIR)lib
#	$(RM) $(TOPDIR)lib/$(LIBNAME)
#	$(INSTALL) -m 644 $(LIBNAME) $(TOPDIR)lib

$(LIBNAME): subdirs ar-target


shared: $(TOPDIR)lib/$(LIBNAME)
	$(LD) $(LDFLAGS) $(VERSION_SCRIPT) -soname=libc.so -o libc.so \
		--whole-archive ../libc/libc.a \
		--no-whole-archive \
		-init __uClibc_init
	$(STRIP) libc.so
	cp libc.so $(SDKDIR)/livecd/iso/system/lib/ -fr

halfclean:
	@$(RM) $(LIBNAME) uClibc_config.h
	@$(RM) $(SHARED_FULLNAME) $(SHARED_MAJORNAME) uClibc-0.* libc.so*

tags:
	ctags -R

clean: subdirs_clean halfclean
	@$(RM) -r tmp
	$(RM) include/asm include/linux include/bits

subdirs: $(patsubst %, _dir_%, $(DIRS))
subdirs_clean: $(patsubst %, _dirclean_%, $(DIRS))

$(patsubst %, _dir_%, $(DIRS)) : dummy
	$(MAKE) -C $(patsubst _dir_%, %, $@)

$(patsubst %, _dirclean_%, $(DIRS)) : dummy
	$(MAKE) -C $(patsubst _dirclean_%, %, $@) clean

.PHONY: dummy subdirs

