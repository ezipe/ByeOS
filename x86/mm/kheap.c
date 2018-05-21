#include "kheap.h"

extern uint32_t KERNEL_END;

static uint32_t* placement_address = KERNEL_END + 0x1000; // 1 page after kernel end

uint32_t _kmalloc(uint32_t size)
{
	uint32_t tmp = placement_address;
	placement_address += size;
	return tmp;
}

uint32_t _kmalloc_a(uint32_t size)
{
	if(placement_address & 0xFFFFF000)
	{
		placement_address &= 0xFFFFF000;
		placement_address += 0x1000;
	}
	uint32_t tmp = placement_address;
	placement_address += size;
	return tmp;
}
uint32_t _kmalloc_p(uint32_t size, uint32_t* phys)
{
	*phys = placement_address;
	return _kmalloc(size);
}
uint32_t _kmalloc_ap(uint32_t size, uint32_t* phys)
{
	*phys = placement_address;
	return _kmalloc_a(size);
}