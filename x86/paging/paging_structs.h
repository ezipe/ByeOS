#ifndef PAGING_STRUCTS_H
#define PAGING_STRUCTS_H
struct page_directory
{
	uint8_t flags;
	uint32_t pt_address;
};
typedef struct page_directory page_directory_t;

struct page_table
{
	uint8_t flags;
	uint32_t page_address;
};
typedef struct page_table page_table_t;

#endif