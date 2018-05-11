#ifndef CMD_QUEUE_H
#define CMD_QUEUE_H

#include <stdlib.h>

#define QUEUE_SIZE 16 // no more than 32 bytes of queue should be good -- fine tune later

#define SUCCESS 0
#define OB_NOT_READY 1
#define IB_NOT_READY 2
#define NO_CMD 3
#define CMD_RESEND 4
#define CMD_FAIL 5

struct queue_entry
{
	uint8_t port;
	uint8_t cmd;
};
typedef struct queue_entry queue_entry_t;

static queue_entry_t queue[QUEUE_SIZE]; 
void queue_init();
int add_cmd(uint8_t port, uint8_t cmd);
int run_cmds();

#endif