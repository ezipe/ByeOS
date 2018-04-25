
SOURCE	:= $(shell find -type f -name "*.c" -print)
OBJ		:= $(SOURCE:.c=.o)

ASM := $(shell find -type f -name "*.asm" -print)
ASM_OBJ := $(ASM:.asm=.o)

default: clean $(OBJ) $(ASM_OBJ)
	
clean: $(shell rm -f $(OBJ))


%.o: %.c
	$(CC) $(CFLAGS) $< -I../stdlib -I../ -o ./obj/$@ $(CLIB)
	
%.o: %.asm
	$(AS) $(ASFLAGS) -f elf32 $< -o ./obj/$@