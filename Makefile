# Binaries to use
CC = gcc -m32
ASM = nasm
LD = ld -m elf_i386

# Compile and link flags
CWARNS = -Wall -Wextra -Wunreachable-code -Wcast-qual -Wcast-align -Wswitch-enum -Wmissing-noreturn -Wwrite-strings -Wundef -Wpacked -Wredundant-decls -Winline -Wdisabled-optimization
CFLAGS = -nostdinc -ffreestanding -fno-builtin -Os $(CWARNS)
AFLAGS = -f elf
LFLAGS = -nostdlib -T linker.ld

# Binary build

test.elf: entry.o test.o
	$(LD) $(LFLAGS) $^ -o $@ 

entry.o: entry.asm
	$(ASM) $(AFLAGS) $< -o $@

test.o: test.c
	$(CC) $(CFLAGS) $< -c -o $@

# ISO build

GENISOIMAGE = genisoimage

test.iso: iso/boot/test.elf
	$(GENISOIMAGE) -o $@ iso

iso/boot/test.elf: test.elf
	@mkdir -p iso/boot
	cp $< $@


# QEMU launchers

QEMU = qemu-system-i386
QFLAGS = -soundhw pcspk

qemu: test.elf
	$(QEMU) $(QFLAGS) -kernel $<

qemu-iso: test.iso
	$(QEMU) $(QFLAGS) -cdrom $<


clean:
	rm -rf test.elf test.o iso test.iso

.PHONY: qemu qemu-iso clean
