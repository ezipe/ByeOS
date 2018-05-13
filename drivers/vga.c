#include "vga.h"
#include <stdlib.h>
 

 

 
void terminal_initialize(void) 
{
	cursor_y = 0;
	cursor_x = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	terminal_clear();
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}


static void move_cursor()
{
	uint16_t cursorLoc = cursor_y * VGA_WIDTH + cursor_x;
	outb(0x3D4, 14); //vga high cursor byte
	outb(0x3D5, cursorLoc >> 8);
	outb(0x3D4, 15); //vga low cursor byte
	outb(0x3D5, cursorLoc);
}
 
static void terminal_scroll()
{
	uint16_t blank = vga_entry(' ', terminal_color);
	
	if(cursor_y >= VGA_HEIGHT)
	{
		size_t i;
		for(i = 0*VGA_WIDTH; i < (VGA_HEIGHT-1)*VGA_WIDTH; i++)
		{
			terminal_buffer[i] = terminal_buffer[i + VGA_WIDTH];
		}
		
		for(i = (VGA_HEIGHT-1)*VGA_WIDTH; i < VGA_HEIGHT*VGA_WIDTH; i++)
		{
			terminal_buffer[i] = blank;
		}
		
		cursor_y = (VGA_HEIGHT-1);

	}
}

void terminal_putchar(char c) 
{
	if(c == '\0')
	#ifdef DISPLAY_NULLS_VGA
		terminal_writestring("NUL");
	#else
		return;
	#endif
	if(c == '\b')
	{
		if(cursor_x-- <= 0)
		{
			cursor_y--;
			cursor_x = VGA_WIDTH-1;
		}
		terminal_putentryat(' ', terminal_color, cursor_x, cursor_y);
		
	}
	else if(c == '\t')
	{
		cursor_x = (cursor_x+8) & ~(8-1);
	}
	else if(c == '\r')
	{
		cursor_x = 0;
	}
	if(c == '\n')
	{
		cursor_y++;
		cursor_x = 0;
	}
	else if(c >= ' ')
	{
		terminal_putentryat(c, terminal_color, cursor_x, cursor_y);
		cursor_x++;
	}
	if (cursor_x >= VGA_WIDTH) 
	{
		cursor_y = 0;
		
	}
	terminal_scroll();
	move_cursor();
	
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void terminal_clear()
{
	for (size_t y = 0; y < VGA_HEIGHT; y++) 
	{
		for (size_t x = 0; x < VGA_WIDTH; x++) 
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	cursor_y = 0;
	cursor_x = 0;
	move_cursor();
}

void terminal_write_hex(uint32_t data)
{
	int32_t tmp;
	
	terminal_writestring("0x");
	
	bool noZeroes = true;
	
	int i;
	for(i = 28; i > 0; i -= 4)
	{
		tmp = (data >> i) & 0xF;
		if(tmp == 0 && noZeroes)
			continue;
		
		if(tmp >= 0xA)
		{
			noZeroes = false;
			terminal_putchar(tmp-0xA+'a');
		}
		else
		{
			noZeroes = false;
			terminal_putchar(tmp+'0');
		}
	}
	
	tmp = data & 0xF;
	if(tmp >= 0xA)
		terminal_putchar(tmp-0xA+'a'+'\0');
	else
		terminal_putchar(tmp+'0'+'\0');
}

void terminal_write_dec(uint64_t data)
{
	if(data == 0)
	{
		terminal_writestring("0");
		return;
		
	}
	int32_t acc = data;
	char c[32];
	int i = 0;
	while(acc > 0)
	{
		c[i] = '0' + acc%10;
		acc /= 10;
		i++;
	}
	c[i] = 0;
	
	char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
	terminal_writestring(c2);
}
