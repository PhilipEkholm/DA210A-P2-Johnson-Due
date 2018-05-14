/*
 * nav_task.c
 *
 * Created: 4/23/2018 11:35:40 AM
 *  Author: Philip Ekholm
 */ 
#include <asf.h>

#include "main_task.h"
#include "pin_mapper.h"
#include "drivers/encoder.h"
#include "TWI.h"
#define MAIN_TASK_PERIODICITY 10

// 	uint8_t array[10] = {};
// 	twi_packet_t packet_pos ={
// 		.addr[0] = 0x00,
// 		.addr [1]=0,
// 		.addr_length =0,
// 		.chip = unoAddress,
// 		.buffer = array,
// 		.length =10,
// 	};

void main_task(void *pvParameters) {
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = MAIN_TASK_PERIODICITY;
	while(1){
		xLastWakeTime = xTaskGetTickCount();
		
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}

