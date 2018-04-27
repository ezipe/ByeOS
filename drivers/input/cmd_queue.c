#include "cmd_queue.h"

static int8_t queue_index = 0;

int add_cmd(uint8_t port, uint8_t cmd)
{
	queue[queue_index].port = port;
	queue[queue_index].cmd = cmd;
	
	if(++queue_index >= QUEUE_SIZE)
	{
		queue_index--; //set it back down & return error code
		return 1;
	}
	return 0;
}

int run_cmds()
{
	uint8_t port = queue[queue_index].port;
	uint8_t cmd = queue[queue_index].cmd;
	if(--queue_index < 0)
	{		
		queue_index = 0;
		return 1;
	}	
	outb(port, cmd);
	return 0;
}