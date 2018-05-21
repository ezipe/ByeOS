
export CC	= i686-elf-gcc
export CFLAGS	=	-std=gnu99 -ffreestanding -g -c

export AS		= nasm
export ASFLAGS	=

export LD				= i686-elf-gcc
export LDFLAGS	= -T linker.ld -ffreestanding -nostdlib -g

MAKEFLAGS = -rR --no-print-directory

default:
	cd boot; make
	cd stdlib; make
	cd x86; make
	cd drivers; make
	cd kernel; make
	$(LD) $(LDFLAGS) boot/obj/*.o kernel/obj/*.o stdlib/obj/*.o x86/obj/*.o \
									 x86/obj/mm/*.o \
									 drivers/obj/*.o \
									 drivers/obj/input/*.o \
									 -o final.bin \
									 
	cp final.bin grubimg/boot/final.bin
	grub-mkrescue -o final.iso grubimg
	
	
all: clean default


clean:
	@find . \( -name '*.o' -o -name '*.SYS' -o -name '*.bin' \) -print -exec rm -f '{}' \;
