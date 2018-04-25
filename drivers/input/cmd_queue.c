#include "cmd_queue.h"

static size_t queue_index = 0;

int add_cmd(queue_entry_t entry)
{
	queue[queue_index] = entry;
	if(++queue_index >= QUEUE_SIZE)
		return 1;
	return 0;
}

void run_cmds()
{
	uint8_t port = queue[queue_index].port;
	uint8_t cmd = queue[queue_index].cmd;
	if(--queue_index < 0) 
		queue_index = 0;
	
	outb(port, cmd);
}