# Automatically expand to a list of existing files that match patterns
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
# Ditto, but object files
OBJ = ${C_SOURCES:.c=.o}

# Default
all : os-image

# Run the os
run : all
	qemu os-image

# Build the os-image
os-image : boot/boot_kernel.bin kernel.bin
	cat $^ > os-image

# This builds the binary of our kernel from two object files :
# - the kernel_entry , which jumps to main () in our kernel
# - the compiled C kernel
kernel.bin : kernel/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rule for compiling C code to object files
# For simplicity, make C files depend on all headers
%.o : %.c ${HEADERS}
	gcc -ffreestanding -c $< -o $@

# Assemble the kernel_entry
%.o : %.asm
	nasm $< -f elf64 -o $@

%.bin : %.asm
	nasm $< -f bin -I '../../16bit/' -o $@

# Build the kernel object file
clean:
	rm -fr *.bin *.o os-image
	rm -fr kernel/*.o boot/*.bin drivers/*.o
