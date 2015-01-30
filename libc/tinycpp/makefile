
include $(SDKDIR)/bin/compile.mk
OBJS=tinycpp.o


CXXFLAGS+=-Wall -pedantic   --no-exceptions -fno-builtin

.cxx.o:
	$(CXX) -I.. $(CXXFLAGS) $< -c

all:  $(OBJS) 
	$(AR) cr libcpp.a $(OBJS)
	cp -fr libcpp.a $(SDKDIR)/uclibc/lib





clean:
	rm -f *.o  *.bak $(OBJS) *.a
