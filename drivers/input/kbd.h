#ifndef KEYBOARD_H
#define KEYBOARD_H


#define MAX_SCANCODE 0xA6

#include <stdlib.h>


static const char scancodes[] = 
{
	'\0',
	'\0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'=',
	'\b',
	'\t',
	'q',
	'w',
	'e',
	'r',
	't',
	'y',
	'u',
	'i',
	'o',
	'p',
	'[',
	']',
	'\n', // ENTER
	'\0', //CTRL
	'a',
	's',
	'd',
	'f',
	'g',
	'h',
	'j',
	'k',
	'l',
	';',
	'\'',
	'`',
	'\0', //LSHIFT
	'\\',
	'z',
	'x',
	'c',
	'v',
	'b',
	'n',
	'm',
	',',
	'.',
	'/',
	'\0', //RSHIFT
	'\0', //PTSCRN
	'\0', //ALT
	' ',
	'\0', //CAPS
	'\0', //F1
	'\0', //F2
	'\0', //F3	
	'\0', //F4
	'\0', //F5
	'\0', //F6
	'2', //F7
	'3', //F8
	'4', //F9
	'\0', //F10
	'\0', //NUM LCK
	'\0', //SCRL LCK
	'\0', //HOME
	'\0', //UP
	'\0', //PG UP
	
	'\0', //NUMPAD KEYS
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0', //END NUMPAD
	
	'\0',  //SH+F1
	'\0', //SH+F2
	'\0', //SH+F3
	'\0', //SH+F4
	'\0', //SH+F5
	'\0', //SH+F6
	'\0', //SH+F7
	'\0', //SH+F8
	'\0', //SH+F9
	'\0', //SH+F10
	'\0', //CONTINUE HERE 0x5E
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0',
	'\0'
	
};

#define BUFFER_SIZE 256

volatile enum 
{
	WAITING,
	KEYCODE_RECEIVED,
	CTRL_CHAR_RECEIVED,
	NEWLINE_RECEIVED
	
} state;



static size_t char_index = 0;

static uint8_t input_buffer[BUFFER_SIZE];

void init_keyboard();
char* read_line();

#endif