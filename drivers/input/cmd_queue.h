#ifndef CMD_QUEUE_H
#define CMD_QUEUE_H

#define QUEUE_SIZE 16 // no more than 32 bytes of queue should be good

struct queue_entry
{
	uint8_t port;
	uint8_t cmd;
};
typedef struct queue_entry queue_entry_t;

volatile static queue_entry_t queue[QUEUE_SIZE]; //ihdk if volatile is necessary here -- it might be

int add_cmd(queue_entry_t entry);
void run_cmds();

#endif