#ifndef KHEAP_H
#define KHEAP_H

#include <libk.h>

//these are internal malloc functions, user-friendly kmalloc is in libk.h, hence the underscores

uint32_t _kmalloc(uint32_t size);
uint32_t _kmalloc_a(uint32_t size);
uint32_t _kmalloc_p(uint32_t size, uint32_t* phys);
uint32_t _kmalloc_ap(uint32_t size, uint32_t* phys);

#endif