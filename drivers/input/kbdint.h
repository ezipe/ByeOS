#ifndef KEYBOARD_INT_H
#define KEYBOARD_INT_H

#include <stdlib.h>
#include <x86/isr.h>

#define BUFFER_SIZE 256

volatile uint8_t scancode_buffer[BUFFER_SIZE];


void init_keyboard_interrupt_handler();

#endif