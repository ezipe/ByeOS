#include "paging.h"


uint32_t* frames;
uint32_t nframes;

extern uint32_t placement_address;

#define INDEX_FROM_BIT(x) (x/(8*4))
#define OFFSET_FROM_BIT(x) (x%(8*4))

static void set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr/0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1 << off);
}

static void clear_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr/0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1 << off);
}

static uint32_t test_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr/0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);
	return (frames[idx] & (0x1 << off));
}

static uint32_t find_first_frame()
{
	for(int i = 0; i < INDEX_FROM_BIT(nframes); i++)
	{
		if(frames[i] != 0xFFFFFFFF)
		{
			for(int j = 0; j < 32; j++)
			{
				uint32_t toTest = 0x1 << j;
				if(!(frames[i]&toTest))
				{
					return i*4*8+j;
				}
			}
		}
	}
}

void alloc_frame(page_t* page, bool is_kernel, bool is_writable)
{
	if(page->frame != 0)
	{
		return;
	}
	else
	{
		uint32_t idx = find_first_frame();
		if(idx == (uint32_t)-1)
		{
			PANIC("No free frames!");
		}
		set_frame(idx*0x1000);
		page->present = 1;
		page->rw = (is_writable)?1:0;
		page->user = (is_kernel)?0:1;
		page->frame = idx;
	}
}

void free_frame(page_t* page)
{
	uint32_t frame;
	if(!(frame=page->frame))
		return;
	else
	{
		clear_frame(frame);
		page->frame = 0x0;
	}
}

void invalidate_page(uint32_t addr)
{
	asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

void set_page_directory(page_directory_t* dir)
{
	asm volatile("mov %0, %%cr3":: "r"(&dir->tables_phys));
}

void enable_paging()
{
	uint32_t cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

void disable_paging()
{
	uint32_t cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 &= ~0x80000000;
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

extern uint64_t total_mem;
void init_paging()
{
	nframes = total_mem / 0x1000;
	frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(nframes), false);
	memset(frames, 0, INDEX_FROM_BIT(nframes));
	
	kernel_directory = (page_directory_t*)kmalloc(sizeof(page_directory_t), true);
	memset(kernel_directory, 0, sizeof(page_directory_t));
	

	
	set_page_directory(kernel_pd);
	enable_paging();
	invalidate_page(0);
}