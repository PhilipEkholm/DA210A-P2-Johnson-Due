/*
 * nav_task.c
 *
 * Created: 4/23/2018 11:35:40 AM
 *  Author: Philip Ekholm
 * updated: Ali Hassan
 */ 
#include <asf.h>

#include "main_task.h"
#include "motor_task.h"
#include "pin_mapper.h"
#include "drivers/encoder.h"
#include "TWI.h"
#define MAIN_TASK_PERIODICITY 10
uint8_t array[10]={};
twi_packet_t packet_pos ={
	.addr[0] = 0x00,	// TWI address/commands to issue to the other chip (node).
	.addr [1]=0,
	.addr_length =0,	// Length of the TWI data address segment (1-3 bytes)
	.chip = unoAddress,		// Adress to Mega kort
	.buffer = array, // where to save packet
	.length =10,	//pakcket length
};

void main_task(void *pvParameters) {
	struct motor_task_instruction inst = {
		.distance = 200,
		.angle = 90,
	};
	
	xQueueSend(motor_task_instruction_handle, &inst, 10);
	while(xQueuePeek(motor_task_instruction_handle, &inst, 10));
	xQueueSend(motor_task_instruction_handle, &inst, 10);
	while(xQueuePeek(motor_task_instruction_handle, &inst, 10));
	xQueueSend(motor_task_instruction_handle, &inst, 10);
	while(xQueuePeek(motor_task_instruction_handle, &inst, 10));
	xQueueSend(motor_task_instruction_handle, &inst, 10);
	while(xQueuePeek(motor_task_instruction_handle, &inst, 10));
	
	while(1){
	}
}

