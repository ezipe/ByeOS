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

struct page_directory
{
	page_table_t *tables[1024];
	uint32_t tables_physical[1024];
	uint32_t physical_addr;
};
typedef struct page_directory page_directory_t;

void set_page_directory(page_directory_t*);
void enable_paging();
void disable_paging();

void init_paging();

page_t* get_page(uint32_t address, int make, page_directory_t*

extern uint64_t KERNEL_VIRTUAL_BASE;

#endif