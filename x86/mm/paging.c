#include "paging.h"

uint32_t kernel_pd[1024] __attribute__((aligned(4096)));
uint32_t first_pt[1024] __attribute__((aligned(4096)));


static void init_pd()
{
	for(unsigned int i = 0; i < 1024; i++)
	{
		kernel_pd[i] = 0x00000002; //supervisor level, r/w, not present
	}
}

static void init_first_pt()
{
	for(unsigned int i = 0; i < 1024; i++)
	{
		first_pt[i] = ((i * 0x1000)) | 3; //supervisor level, r/w, present
	}
	kernel_pd[0] = ((unsigned int)first_pt) | 3; //supervisor level, r/w, present
}

void invalidate_page(uint32_t addr)
{
	asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

void init_paging()
{
	init_pd();
	init_first_pt();
	set_page_directory(kernel_pd);
	enable_paging();
	invalidate_page(0);
}