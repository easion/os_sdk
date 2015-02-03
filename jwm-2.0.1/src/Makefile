
CC = $(CROSSCOMPILER)gcc 
LD = $(CROSSCOMPILER)ld
STRIP = $(CROSSCOMPILER)strip
CFLAGS = -g -O2 -I$(SDKDIR)/uclibc/include -I$(SDKDIR)/uclibc/include/freetype2 -I../../../exports/include   
#CFLAGS += -DDEBUG
LDFLAGS = -L../../../exports/lib -lXpm -ltinyX11 -lpng   -ljpeg -lz
BINDIR = /usr/local/bin

VPATH=.:os

OBJECTS = background.o border.o button.o client.o clientlist.o clock.o \
	color.o command.o confirm.o cursor.o debug.o desktop.o dock.o event.o \
   error.o font.o gradient.o group.o help.o hint.o icon.o image.o \
   key.o lex.o main.o match.o menu.o misc.o move.o outline.o pager.o \
   parse.o place.o popup.o render.o resize.o root.o screen.o status.o \
   swallow.o taskbar.o timing.o tray.o traybutton.o winmenu.o

EXE = jwm

.SUFFIXES: .o .h .c

all: $(EXE)

install: all
	strip $(EXE)
	install -d $(BINDIR)
	install $(EXE) $(BINDIR)/$(EXE)

depend:
	makedepend -m -DMAKE_DEPEND -- $(CFLAGS) -- *.c

$(EXE).1: $(OBJECTS)
#	$(CC) -o $(EXE) $(OBJECTS) $(LDFLAGS)
	i386-elf-ld  -nostdlib -nostdinc -Ttext 0x10000 -o  $(EXE) $(SDKDIR)/uclibc//lib/crt1.o $(OBJECTS)   -L$(SDKDIR)/uclibc//lib/ $(LDFLAGS) -lm -lnetbas   -lc -lgcc 
	i386-elf-strip -s   $(EXE)  
	cp -fr   $(EXE)  $(SDKDIR)/livecd/iso/system/bin/

$(EXE): $(OBJECTS) $(MAKEDEP)
#	$(LD) -nostdlib  -Bdynamic --nostdlib --script=$(SDKDIR)/bin/app.ld -o $@ $(SDKDIR)/uclibc//lib/crt0.o $^     $(SDKDIR)/livecd/iso/system/lib/Xrender.so $(SDKDIR)/livecd/iso/system/lib/libXext.so  $(SDKDIR)/livecd/iso/system/lib/libX11.so  $(SDKDIR)/livecd/iso/system/lib/libpng.so $(SDKDIR)/livecd/iso/system/lib/libjpeg.so   $(SDKDIR)/livecd/iso/system/lib/libexpat.so -L$(SDKDIR)/uclibc//lib/ -L../../exports/lib -lXpm -lz -lm -lnetbas   -lc -lgcc  
	$(LD) -nostdlib  -Bdynamic --nostdlib --script=$(SDKDIR)/bin/app.ld -o $@ $(SDKDIR)/uclibc//lib/crt0.o $^       $(SDKDIR)/livecd/iso/system/lib/libX11.so $(SDKDIR)/livecd/iso/system/lib/libgi.so $(SDKDIR)/livecd/iso/system/lib/libpng.so $(SDKDIR)/livecd/iso/system/lib/libjpeg.so   $(SDKDIR)/livecd/iso/system/lib/libfreetype.so -L$(SDKDIR)/uclibc//lib/ -L../../exports/lib -lXpm -lz -lm -lnetbas   -lc -lgcc  
	$(STRIP)  $@ 
	cp -fr  $@  $(SDKDIR)/livecd/iso/system/bin/

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJECTS) $(EXE) core

