#include "stdlib.h"

#include <drivers/vga.h>

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
	
	return (void*)dest;
}
void *memmove(void *s1, const void *s2, size_t n)
{
	unsigned char *dest = (unsigned char*)s1;
	unsigned char *src = (unsigned char*)s2;
	
	if(dest < src + n && dest > src)
	{
		src += n;
		dest += n;
		
		for(;((uintptr_t)dest & (sizeof(unsigned long)-1)) && n > 0; )
		{
			src--, dest--, n--;
			*dest = *src;
		}
		
		unsigned long *w_src = (unsigned long*)src;
		unsigned long *w_dest = (unsigned long*)dest;
		for(; n >= sizeof(unsigned long); )
		{
			w_src--, w_dest--, n -= sizeof(unsigned long);
			*w_dest = *w_src;
		}
		
		src = (unsigned char*)w_src;
		dest = (unsigned char*)w_dest;
		for(; n>0;)
		{
			src--, dest--, n--;
			*dest = *src;
		}
	}
	else
	{
		for (;((uintptr_t)dest & (sizeof(unsigned long)-1)) && n > 0; src++, dest++, n--)
        {
            *dest = *src;
        }

        
        unsigned long *w_src  = (unsigned long *)src;
        unsigned long *w_dst = (unsigned long *)dest;
        for (;n >= sizeof(unsigned long); w_src++, w_dst++, n -= sizeof(unsigned long))
        {
            *w_dst = *w_src;
        }

       
        src  = (unsigned char *)w_src;
        dest = (unsigned char *)w_dst;
        for (; n > 0; src++, dest++, n--)
        {
            *dest = *src;
		}
	}
	return (void*)s2;
}
int memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *b_p1 = (unsigned char*)s1;
	unsigned char *b_p2 = (unsigned char*)s2;
	
	for(;((uintptr_t)b_p1 & (sizeof(long)-1)) && n > 0; ++b_p1, ++b_p2, --n)
	{
		if(*b_p1 != *b_p2)
		{
			return *b_p1 > *b_p2 ? 1 : -1;
		}
	}
	
	unsigned long *w_p1 = (unsigned long *)b_p1;
    unsigned long *w_p2 = (unsigned long *)b_p2;
    for (;n >= sizeof(unsigned long); ++w_p1, ++w_p2, n -= sizeof(unsigned long))
    {
        if (*w_p1 != *w_p2)
        {
            return *w_p1 > *w_p2 ? 1 : -1;
        }
	}
	
	b_p1 = (unsigned char *)w_p1;
    b_p2 = (unsigned char *)w_p2;
    for (; n > 0; ++b_p1, ++b_p2, --n)
    {
        if (*b_p1 != *b_p2)
        {
            return *b_p1 > *b_p2 ? 1 : -1;
        }
	}
	
	return 0;
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

int isprint(int c)
{
	
	return ((c >= ' ' && c <= '~') ? 1 : 0);

}

int putchar(int c)
{
	terminal_putchar(c);
	return 0;
}

int puts(const char *s)
{
	terminal_writestring(s);
	terminal_putchar('\n');
	return 0;
}