# caleb-os

Operating system written in C and x86 Assembly for an i386 processor, created for Ahmed Banafa's CS 421 class at California State University East Bay, Summer 23

![caleb-os demo](https://github.com/Sepulchre49/caleb-os/assets/25937672/602f8f96-6ba1-45c8-8fdc-fcb7e610ffaa)

# Resources Used
*Writing a Simple Operating System - From Scratch* by Nick Blundell (https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)  
*os-tutorial* by Carlos Fenollosa (https://github.com/cfenollosa/os-tutorial)  
*Roll your own toy UNIX-clone OS* by James Molloy (http://www.jamesmolloy.co.uk/tutorial_html/)  

# Building & Running
This project was built for an i386 processor. You'll need a gcc cross-compiler and binutils targeting this architecture to build  
Further, you'll need qemu-system-i386 installed to run  
Run `make run` to automatically build the os-image and launch in qemu  
Run `make debug` to automatically build with debugging symbols, launch in qemu with -S flag, and launch gdb. If you have the .gdb file that comes with this repository, gdb should attach to the qemu instance, load the debugging symbols, and set a breakpoint in the kernel's main function  

