del *.o
del *.bak 
set PATH=F:\tools\i386-elf\bin
yasm -f elf -o crt0.o crt0.asm
yasm -f elf -o crti.o crti.asm
i386-elf-g++ -c -nostdinc crt_cppinit.cpp
i386-elf-ld -r -o crt1.o crti.o crt_cppinit.o 
pause