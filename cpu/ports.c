#include "ports.h"

u8int port_byte_in(u16int port) {
    // A C wrapper function which reads a byte from the specified port
    // "=a" (result) means: put AL register in variable RESULT when finished
    // "d" (port) means: load EDX with port
    u8int result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(u16int port, u8int data) {
    // "a" (data) means: load EAX with data
    // "d" (port) means: load EDX with port
    __asm__("out %%al, %%dx" :  : "a" (data), "d" (port));
}

u16int port_word_in(u16int port) {
    u16int result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out(u16int port, u16int data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}