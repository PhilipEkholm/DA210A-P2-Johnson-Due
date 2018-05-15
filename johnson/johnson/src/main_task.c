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
	/*
	I2C_master_read(TWI1,&packet_pos);
	while(1){
		printf("--Arduino Due Master--\n");
		printf("---------------------------\n");
		printf("received Packet from Slave:[");
		for(int i = 0; i < 10; i++){
			printf("%d ", array[i]);		}
		printf("]\n");
		printf("---------------------------\n");
	}
	*/
	
	while(1){
		struct motor_task_instruction inst = {
			.distance = 5,
			.angle = 180	
		};
		
		/* Instruction successfully sent to motor task */
		if (xQueueSend(motor_task_instruction_handle, &inst, 10)) {
			
		}
		/* Motor task busy, wait until stop */
		else {
			
		}
	}
}

