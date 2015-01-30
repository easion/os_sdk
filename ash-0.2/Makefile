#	Makefile,v 1.7 1993/08/09 04:58:18 mycroft Exp


include $(SDKDIR)/bin/compile.mk

PROG=	sh
SRCS=	builtins.c cd.c dirent.c echo.c error.c eval.c exec.c expand.c \
	input.c jobs.c mail.c main.c memalloc.c miscbltin.c \
	mystring.c nodes.c options.c parser.c redir.c show.c \
	syntax.c trap.c output.c var.c test.c

OBJ1 =	init.o
OBJ2 =	builtins.o cd.o dirent.o echo.o error.o eval.o exec.o expand.o \
	input.o jobs.o mail.o main.o memalloc.o miscbltin.o \
	mystring.o nodes.o options.o parser.o redir.o show.o \
	syntax.o trap.o output.o var.o test.o\
	bltin/touch.o bltin/uname.o bltin/netbas.o

OBJS =	$(OBJ1) $(OBJ2)

#CFLAGS = -O2 -pipe -DSHELL -I/usr/include/bsd -I. -D__BIT_TYPES_DEFINED__
#LDFLAGS = -s -lbsd
CFLAGS += -O2  -DSHELL -I. -D__BIT_TYPES_DEFINED__

CLEANFILES =\
	builtins.c builtins.h init.c mkinit mknodes mksyntax \
	nodes.c nodes.h syntax.c syntax.h token.def

all:	$(OBJS)
	$(LD)  $(LCFLAG) -o $(PROG) $(CRT0)    $(OBJS)  $(LINKLIB) 
#	$(CC) -static -o $(PROG) $(OBJS) $(LDFLAGS)
	$(STRIP)  $(PROG) 

install: all
	install sh /bin/ash
	install -m 644 sh.1 /usr/man/man1/ash.1

parser.o: token.def
token.def: mktokens
	sh ./mktokens

builtins.h builtins.c: mkbuiltins
	sh ./mkbuiltins

#init.c: mkinit $(SRCS)
#	./mkinit '${CC} -c $(CFLAGS) init.c' $(SRCS)
#	touch init.c

mkinit: mkinit.c
	$(CC) $(CFLAGS) $(LDFLAGS) mkinit.c -o $@ $(LDADD)

nodes.c nodes.h: mknodes nodetypes nodes.c.pat
	./mknodes nodetypes nodes.c.pat

mknodes: mknodes.c
	$(CC) $(CFLAGS) $(LDFLAGS) mknodes.c -o $@ $(LDADD)

syntax.c syntax.h: mksyntax
	./mksyntax

mksyntax: mksyntax.c parser.h
	$(CC) $(CFLAGS) $(LDFLAGS) mksyntax.c -o $@ $(LDADD)

clean:
	rm -f  $(OBJS)

