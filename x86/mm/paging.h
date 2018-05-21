#ifndef PAGE_DIRECTORY_H
#define PAGE_DIRECTORY_H

#include <libk.h>

struct page
{
	uint32_t present : 	 1;
	uint32_t rw :		 1;
	uint32_t user :		 1;
	uint32_t accessed :	 1;
	uint32_t dirty : 	 1;
	uint32_t unused :	 7;
	uint32_t frame : 	 20;
};
typedef struct page page_t;
struct page_table
{
	page_t pages[1024];
};
typedef struct page_table page_table_t;

extern void set_page_directory(unsigned int*);
extern void enable_paging();
extern void disable_paging();

void init_paging();

extern uint64_t KERNEL_VIRTUAL_BASE;

#endif