

OBJS =  socket.o inet_addr.o inet_aton.o inet_ntoa.o gethostname.o\
domainname.o getnetent.o h_errno.o inet_net.o gethostent.o netdb.o\
resolv.o crypt.o


# libc stdio makefile
LIBC_STDIO_DIR := net/

MY_OBJS += \
 $(LIBC_STDIO_DIR)/gethostent.o  $(LIBC_STDIO_DIR)/netdb.o\
$(LIBC_STDIO_DIR)/resolv.o  $(LIBC_STDIO_DIR)/crypt.o

TMP_OBJ=\
$(LIBC_STDIO_DIR)/inet_net.o \
 $(LIBC_STDIO_DIR)/socket.o  $(LIBC_STDIO_DIR)/inet_addr.o  $(LIBC_STDIO_DIR)/inet_aton.o  \
 $(LIBC_STDIO_DIR)/inet_ntoa.o  $(LIBC_STDIO_DIR)/gethostname.o\
$(LIBC_STDIO_DIR)/domainname.o  $(LIBC_STDIO_DIR)/getnetent.o  $(LIBC_STDIO_DIR)/h_errno.o  \

