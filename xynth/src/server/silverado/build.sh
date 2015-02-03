rm -f *.o *.so *.bak

i386-elf-gcc -I../../lib -I../../server -I../../../../librtl -I../../../../libc/include -I../../../../posix/include -Wall -g -pipe -nostdlib -nostdinc -I/d/jicamasdk//uclibc//include -I/d/jicamasdk//uclibc//include/SDL -c  -MD -MT -MF -o silverado.o silverado.c
i386-elf-ld  -shared -soname netbas.so --script=/d/jicamasdk//bin/templates/library.ld -o silverado.so silverado.o

echo done

