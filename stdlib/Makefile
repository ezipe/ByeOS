
export CC	= i686-elf-gcc
export CFLAGS	=	-std=gnu99 -ffreestanding -g -c

export AS		= nasm
export ASFLAGS	=


SOURCE	:= $(shell find -type f -name "*.c" -print)
OBJ		:= $(SOURCE:.c=.o)

ASM := $(shell find -type f -name "*.asm" -print)
ASM_OBJ := $(ASM:.asm=.o)

default: clean $(OBJ) $(ASM_OBJ)
	
clean: $(shell rm -f $(OBJ))


%.o: %.c
	$(CC) $(CFLAGS) $< -I../ -o ./obj/$@ $(CLIB)
	
%.o: %.asm
	$(AS) $(ASFLAGS) -f elf32 $< -o ./obj/$@