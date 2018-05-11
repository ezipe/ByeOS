#ifndef PS2_H
#define PS2_H

#include "kbd.h"
#include <stdlib.h>
#include "../vga.h"

void ps2_wait_in();
void ps2_wait_out();

uint16_t init_ps2();


#endif