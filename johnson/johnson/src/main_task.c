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

void main_task(void *pvParameters) {
	while(1){
		ioport_set_pin_level(pin_mapper(TASK_DEBUG_MAIN_PIN), 1);
		ioport_set_pin_level(pin_mapper(TASK_DEBUG_MAIN_PIN), 0);
	}
}

