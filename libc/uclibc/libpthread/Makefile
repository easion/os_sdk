

TOPDIR=../../
include $(TOPDIR)Rules.mak

MSRC=
MOBJ=	



CSRC=attr.c cond.c mutex.c pthread.c rwlock.c bits.c 


COBJ=$(patsubst %.c,%.o, $(CSRC))
OBJS=$(MOBJ) $(COBJ)

all: $(OBJS) $(LIBC)

$(LIBC): ar-target

ar-target: $(OBJS)
	$(AR) $(ARFLAGS) $(LIBC) $(OBJS)

$(MOBJ): $(MSRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(STRIPTOOL) -x -R .note -R .comment $*.o

$(COBJ): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	$(STRIPTOOL) -x -R .note -R .comment $*.o

$(OBJ): Makefile

__getgrent_r.c: config.h
initgroups.c: config.h

clean:
	$(RM) *.[oa] *~ core
