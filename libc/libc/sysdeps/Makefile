
# libc stdio makefile
LIBC_STDIO_DIR := sysdeps

MY_OBJS += \
	 $(LIBC_STDIO_DIR)/gfx.o  $(LIBC_STDIO_DIR)/mmap.o  $(LIBC_STDIO_DIR)/znxml.o\
	 $(LIBC_STDIO_DIR)/int86.o  $(LIBC_STDIO_DIR)/farptr.o \
	 $(LIBC_STDIO_DIR)/dll/dlopen.o  $(LIBC_STDIO_DIR)/dll/coff.o\
	 $(LIBC_STDIO_DIR)/dll/djcoff.o  $(LIBC_STDIO_DIR)/dll/elf.o\
	 $(LIBC_STDIO_DIR)/dll/dlsym.o  \
	$(LIBC_STDIO_DIR)/thread/thread.o  $(LIBC_STDIO_DIR)/thread/msgport.o\
	$(LIBC_STDIO_DIR)/images/huff.o  $(LIBC_STDIO_DIR)/images/jpeg.o\
	$(LIBC_STDIO_DIR)/images/main.o  $(LIBC_STDIO_DIR)/images/vesa.o

LIBC_POSIX_DIR := sysdeps

# include sub makefiles
include $(addsuffix /Makefile, $(addprefix $(MY_SRCDIR)/$(LIBC_POSIX_DIR)/, \
	syscall \
))

