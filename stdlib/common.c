#include "common.h"

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16_t inw(uint16_t port)
{
   uint16_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
} 

void *memset(void *s, int c, size_t n)
{
	unsigned char* p=s;
	while(n--)
		*p++ = (unsigned char)c;
	return s;
}

void *memcpy(void *s, const void *dest, size_t n)
{
	char *cs = (char *)s;
	char *cdest = (char*)dest;
	
	for(size_t i = 0; i < n; i++)
		cdest[i] = cs[i];
}

int strcmp(const char *s1, const char *s2)
{
	while(*s1)
	{
		if(*s1 != *s2)
			break;
		
		s1++;
		s2++;
	}
	
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}
