#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

void *memset(void *s, int c, size_t n);
void *memcpy(void *s, const void *s2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

int strcmp(const char *s1, const char *s2);
int isprint(int c);
size_t strlen(const char* str);

int putchar(int c);
int puts(const char *s);

#endif