# ByeOS
A simple hobby OS
## BUILD INSTRUCTIONS

### PREREQUISITES
* Linux, or a compatible build system (Cygwin, MinGW, Ubuntu for Windows)
* A cross-compiler for i686-elf (instructions on how to build a cross compiler can be found [here](https://wiki.osdev.org/GCC_Cross-Compiler)
* GRUB 2 + xorriso for ISO generation 
### BUILD
1. Run `make` using your favorite terminal. Really, it's that easy!

### FAQ
FATAL: Can't create obj/...: No such file or directory:
* Make sure you have created obj folders in all of the source folders. If anybody knows how to get make to do that automatically, that would be great

## USAGE
This OS can be run on real hardware, on in an emulator. It has been tested to work with Oracle VirtualBox, however if you have tested it with any other emulators please let me know.
