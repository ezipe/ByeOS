#include "cmd_queue.h"


static int8_t queue_index = 0;
static uint8_t current_cmd = 0;

static uint8_t failures = 0;

static bool cmd_run = 0;

void queue_init()
{
	memset(queue, 0, sizeof(queue));
}

int add_cmd(uint8_t port, uint8_t cmd)
{
	size_t index = queue_index % QUEUE_SIZE;
	queue[index].port = port;
	queue[index].cmd = cmd;
	
	queue_index++;
	
	return 0;
}

int run_cmds()
{
	size_t index = current_cmd % QUEUE_SIZE;
	uint8_t port = queue[index].port;
	uint8_t cmd = queue[index].cmd;
	if(port == 0 && cmd == 0) return NO_CMD;
	if(inb(0x64) & 1<<1) return OB_NOT_READY;	
	
	if(!cmd_run)
	{
		outb(port, cmd);
		cmd_run = true;
	}
	if(!(inb(0x64) && 1<<0))
	{
		
		return IB_NOT_READY ;
	}
	else
	{
		cmd_run = false;
	}
	
	uint8_t response = inb(port);
	if(response == 0xFA)
	{
		queue[index].port = 0;
		queue[index].cmd = 0;
		
		current_cmd++;
	}
	else if (response == 0xFE)
	{
		failures++;
		if(failures >= 4)
		{
			queue[index].port = 0;
			queue[index].cmd = 0;
		
			current_cmd++;
			failures = 0;
			return CMD_FAIL;
		}
		return CMD_RESEND;
	}
	return SUCCESS;
}