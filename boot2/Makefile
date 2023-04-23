CC = gcc -m32
CFLAGS = -ffreestanding -Wall -Wextra -fno-pie -I. -Ilib
#CSRC = $(shell find . -type f -name '*.c')

build:
	mkdir -p bin
	$(CC) $(CFLAGS) kmain.cpp -c
	mv *.o bin
	nasm -felf32 boot2.asm -o bin/boot2.o
	$(CC) -T linker.ld bin/*.o -o bin/boot2.bin -nodefaultlibs -nostartfiles -no-pie 
#-lgcc
#	nasm -fbin boot/boot.asm -o ../game

launch: build
	qemu-system-x86_64 bin/boot2.bin -no-reboot -monitor stdio -d int -D qemu.log -no-shutdown